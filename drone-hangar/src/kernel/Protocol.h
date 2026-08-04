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
#define DRONE_REST      "REST"
#define DRONE_TAKEOFF   "TAKEOFF"
#define DRONE_OUT       "OUT"
#define DRONE_LANDING   "LANDING"

// hangar states
#define HANGAR_NORMAL   "NORMAL"
#define HANGAR_PREALARM "PREALARM"
#define HANGAR_ALARM    "ALARM"

#endif