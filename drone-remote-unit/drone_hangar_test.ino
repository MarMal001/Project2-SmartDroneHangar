/*
 * Questo sketch NON legge nessun componente reale. Serve solo a
 * verificare che il protocollo seriale con l'applicazione Java (DRU)
 * funzioni. Tutti i dati sono simulati internamente.
 *
 * Protocollo (una riga per messaggio, terminata da '\n'):
 *
 *   Arduino -> PC
 *     st:<droneState>:<hangarState>:<distanceCm>
 *     al:ALARM
 *     lo:<testo libero>
 *
 *   PC -> Arduino
 *     cmd:OPEN
 */

//stati simulati 
#include <Arduino.h>
enum DroneState { D_REST, D_TAKEOFF, D_OUT, D_LANDING };
enum HangarState { H_NORMAL, H_PREALARM, H_ALARM };

DroneState droneState = D_REST;
HangarState hangarState = H_NORMAL;
int simulatedDistance = 0;

//parametri di simulazione

const unsigned long DOOR_PHASE_MS   = 3000;   // durata simulata di takeoff e atterraggio
const unsigned long STATUS_PERIOD_MS = 500;   // periodo di invio dello stato
const unsigned long TEMP_CYCLE_MS   = 40000;  // periodo del ciclo di temperatura finta
const unsigned long PREALARM_HOLD_MS = 4000;  // T3 simulato
const unsigned long ALARM_HOLD_MS    = 4000;  // T4 simulato
const unsigned long AUTO_RESET_DELAY_MS = 10000; // "operatore" simulato che preme RESET

const float TEMP1 = 32.0;
const float TEMP2 = 40.0;

//variabili di temporizzazione

unsigned long lastStatusSend = 0;
unsigned long doorPhaseStart = 0;
unsigned long tempThresholdSince = 0;
unsigned long alarmSince = 0;

bool doorPhaseActive = false;

// buffer di ricezione comandi dal dru

String inputBuffer = "";

void setup() {
  Serial.begin(115200);
  sendLog("Drone Hangar TEST avviato (dati simulati, nessun sensore reale)");
  sendStatus();
}

void loop() {
  readSerialCommands();
  updateSimulatedTemperature();
  updateDoorPhase();

  unsigned long now = millis();
  if (now - lastStatusSend >= STATUS_PERIOD_MS) {
    lastStatusSend = now;
    sendStatus();
  }
}


// Lettura comandi dal D.R.U.

void readSerialCommands() {
  while (Serial.available() > 0) {
    char c = (char) Serial.read();
    if (c == '\n') {
      inputBuffer.trim();
      if (inputBuffer.length() > 0) {
        handleCommand(inputBuffer);
      }
      inputBuffer = "";
    } else if (c != '\r') {
      inputBuffer += c;
    }
  }
}

void handleCommand(String cmd) {
  sendLog("Comando ricevuto: '" + cmd + "'");
  if (cmd == "cmd:OPEN") {
    onOpenCommand();
  } else {
    sendLog("Comando non riconosciuto: " + cmd);
  }
}

void onOpenCommand() {
  if (hangarState == H_ALARM) {
    sendLog("Comando OPEN ignorato: sistema in ALARM, serve RESET");
    return;
  }
  if (droneState == D_REST) {
    droneState = D_TAKEOFF;
    doorPhaseActive = true;
    doorPhaseStart = millis();
    sendLog("Apertura porta: decollo in corso");
  } else if (droneState == D_OUT) {
    droneState = D_LANDING;
    doorPhaseActive = true;
    doorPhaseStart = millis();
    simulatedDistance = 150;
    sendLog("Apertura porta: atterraggio in corso");
  } else {
    sendLog("Comando OPEN ignorato: fase gia' in corso");
  }
}


// Simulazione fasi decollo/atterraggio (equivalente dei DDD e DPD)


void updateDoorPhase() {
  if (!doorPhaseActive) {
    return;
  }
  unsigned long elapsed = millis() - doorPhaseStart;

  if (droneState == D_LANDING) {
    // simuliamo la distanza che scende linearmente verso 0
    long remaining = (long) DOOR_PHASE_MS - (long) elapsed;
    if (remaining < 0) remaining = 0;
    simulatedDistance = (int) (150L * remaining / (long) DOOR_PHASE_MS);
  }

  if (elapsed >= DOOR_PHASE_MS) {
    doorPhaseActive = false;
    if (droneState == D_TAKEOFF) {
      droneState = D_OUT;
      sendLog("Drone uscito (simulato): porta chiusa");
    } else if (droneState == D_LANDING) {
      droneState = D_REST;
      simulatedDistance = 0;
      sendLog("Drone atterrato (simulato): porta chiusa");
    }
  }
}

void updateSimulatedTemperature() {
  unsigned long now = millis();
  float phase = (now % TEMP_CYCLE_MS) / (float) TEMP_CYCLE_MS; // 0..1
  float simulatedTemp = 20.0 + 25.0 * phase; // sale da 20 a 45 e poi riparte

  if (hangarState == H_ALARM) {
    // in ALARM restiamo bloccati finche' non arriva il reset
    if (alarmSince != 0 && now - alarmSince >= AUTO_RESET_DELAY_MS) {
      simulateOperatorReset();
    }
    return;
  }

  if (simulatedTemp >= TEMP2) {
    if (tempThresholdSince == 0) tempThresholdSince = now;
    if (now - tempThresholdSince >= ALARM_HOLD_MS) {
      enterAlarm();
    }
  } else if (simulatedTemp >= TEMP1) {
    if (hangarState == H_NORMAL) {
      if (tempThresholdSince == 0) tempThresholdSince = now;
      if (now - tempThresholdSince >= PREALARM_HOLD_MS) {
        hangarState = H_PREALARM;
        sendLog("Temperatura simulata sopra soglia 1: PRE-ALARM");
      }
    }
  } else {
    if (hangarState == H_PREALARM) {
      hangarState = H_NORMAL;
      sendLog("Temperatura simulata rientrata: NORMAL");
    }
    tempThresholdSince = 0;
  }
}

void enterAlarm() {
  hangarState = H_ALARM;
  alarmSince = millis();
  tempThresholdSince = 0;

  // se una fase era in corso, viene interrotta
  doorPhaseActive = false;
  if (droneState == D_TAKEOFF || droneState == D_LANDING) {
    droneState = (droneState == D_TAKEOFF) ? D_REST : D_OUT;
  }

  sendLog("Temperatura simulata sopra soglia 2: ALARM");
  Serial.println("al:ALARM");
}

void simulateOperatorReset() {
  hangarState = H_NORMAL;
  alarmSince = 0;
  sendLog("RESET simulato dall'operatore: sistema tornato NORMAL");
}


// Invio log e status 


void sendStatus() {
  Serial.print("st:");
  Serial.print(droneStateName());
  Serial.print(":");
  Serial.print(hangarStateName());
  Serial.print(":");
  Serial.println(simulatedDistance);
}

void sendLog(String msg) {
  Serial.print("lo:");
  Serial.println(msg);
}

const char* droneStateName() {
  switch (droneState) {
    case D_REST: return "REST";
    case D_TAKEOFF: return "TAKEOFF";
    case D_OUT: return "OUT";
    case D_LANDING: return "LANDING";
  }
  return "REST";
}

const char* hangarStateName() {
  switch (hangarState) {
    case H_NORMAL: return "NORMAL";
    case H_PREALARM: return "PREALARM";
    case H_ALARM: return "ALARM";
  }
  return "NORMAL";
}