# Drone Remote Unit (DRU) - Java/Swing


## Compilazione (JDK 21)

```bash
cd dru-java
mkdir -p bin
javac -d bin -cp lib/jssc-2.9.4.jar src/esiot/dronehangar/*.java
```

## Esecuzione

Su Linux la porta e' tipicamente `/dev/ttyACM0` o `/dev/ttyUSB0`
(ho verificvato con con `ls /dev/tty*` prima e dopo aver collegato Arduino).
Su Windows sara' qualcosa come `COM3`.

```bash
java -cp "bin:lib/jssc-2.9.4.jar" esiot.dronehangar.DroneRemoteUnitLauncher /dev/ttyUSB0
```

Se non si passa nessun argomento viene usato il default definito in
`DroneRemoteUnitLauncher.java` (`/dev/ttyUSB0`), da modificatelo se lo conosci.

## Test

Comportamento atteso durante il test:
- ogni 500 ms l'Arduino invia lo stato corrente (`st:...`);
- premendo "Take Off" nel DRU il drone passa a TAKEOFF poi a OUT dopo
  ~3 second;
- premendo "Land" quando e' OUT, passa a LANDING con distanza che
  scende verso 0, poi torna REST;
- la temperatura simulata sale e scende in un ciclo di 40 secondi:
  si potra' osservare il passaggio a PRE-ALARM e poi ad ALARM (con
  popup nel DRU), seguito da un reset automatico "simulato" dopo 5
  secondi, forse l'ho messo a 10 (al posto della pressione del pulsante RESET fisico).
