#ifndef _ALARM_H
#define _ALARM_H
#include <string.h>
#include <system.h>
#include <core/serial.h>

void createAlarmProcess(); // Create Process

void addAlarm(char* message, char* alarmTime);
// Command for terminal
#endif
