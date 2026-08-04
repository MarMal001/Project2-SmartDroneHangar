#ifndef __SERIAL_COMM__
#define __SERIAL_COMM__

#include "Arduino.h"

//pensata per task periodiche
class SerialCommService {

public:
  SerialCommService();

  // Legge i byte disponibili sulla Serial e aggiorna lo stato interno.
  void poll();

  // true se dall'ultima consumeOpenCommand() e' arrivato un "cmd:OPEN".
  bool isOpenCommandPending();

  // Consuma il comando di apertura pendente (lo resetta a false).
  void consumeOpenCommand();

  // Invia "st:<droneState>:<hangarState>:<distanceCm>"
  void sendState(const String& droneState, const String& hangarState, int distanceCm);

  // Invia "al:ALARM"
  void sendAlarm();

  // Invia "al:PREALARM"
  void sendPreAlarm();

private:
  void processMessage(const String& msg);

  String inputBuffer;
  bool openCommandPending;
};

extern SerialCommService SerialComm;

#endif