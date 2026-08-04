#ifndef __SERIAL_COMM__
#define __SERIAL_COMM__

#include <Arduino.h>

//pensata per task periodiche
class SerialCommService {

public:
    // Legge i byte disponibili sulla Serial e aggiorna lo stato interno.
    static void poll();

    // true se dall'ultima consumeOpenCommand() e' arrivato un "cmd:OPEN".
    static bool isOpenCommandPending();

    // Consuma il comando di apertura pendente (lo resetta a false).
    static void consumeOpenCommand();

    // Invia "st:<droneState>:<hangarState>:<distanceCm>"
    static void sendState(const String& droneState, const String& hangarState, int distanceCm);

    // Invia "al:ALARM"
    static void sendAlarm();

    // Invia "al:PREALARM"
    static void sendPreAlarm();

    static SerialCommService getInstance();

private:
    static void processMessage(const String& msg);

    SerialCommService();

private:
    static SerialCommService instance;

    String inputBuffer;
    bool openCommandPending;
};

#endif