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
