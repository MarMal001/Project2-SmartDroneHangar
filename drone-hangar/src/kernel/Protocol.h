#ifndef __PROTOCOL__
#define __PROTOCOL__

// Baud rate atteso dal DRU (specificato in DroneRemoteUnitLauncher.java)
constexpr unsigned long SERIAL_BAUD_RATE = 115200uL;

// prefissi messaggio
#define STATE_PREFIX    "st:"
#define ALARM_PREFIX    "al:"
#define LOG_PREFIX      "lo:"

// comando ricevuto dal DRU
#define CMD_OPEN "cmd:OPEN"

// drone states
#define MSG_DRONE_REST      "REST"
#define MSG_DRONE_TAKEOFF   "TAKEOFF"
#define MSG_DRONE_OUT       "OUT"
#define MSG_DRONE_LANDING   "LANDING"

// hangar states
#define MSG_HANGAR_NORMAL   "NORMAL"
#define MSG_HANGAR_PREALARM "PREALARM"
#define MSG_HANGAR_ALARM    "ALARM"

#endif