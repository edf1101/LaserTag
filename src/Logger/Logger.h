/*
 * Created by Ed Fillingham on 20/07/2024.
 *
 * This is a proprietary logger class that primarily logs messages to the serial port.
 * It also can be used to stop and power off the device if a fatal error occurs.
*/

#ifndef LASERTAG_LOGGER_H
#define LASERTAG_LOGGER_H

#include <string>
#include <vector>
#include "Arduino.h"
#include "../Network/MessageQueue.h"



class Logger {
public:

    enum class LogLevel { // enum to represent the level of logging
        DETAIL,
        INFO,
        ERROR,
        FATAL
    };

    static void init(bool _serialOn, unsigned long _baudRate, LogLevel _loggerLevel); // Initialises the logger

    static void log(LogLevel level, std::string message); // Logs a message to the system

    static Networks::MessageQueue* getLogBuffer(); // Returns the log buffer
private:
    inline static Networks::MessageQueue logBuffer; // Buffer to store the logs

    inline static bool serialOn; // Whether the serial port is on
    inline static LogLevel loggerLevel; // The level of logging to output

};


#endif //LASERTAG_LOGGER_H
