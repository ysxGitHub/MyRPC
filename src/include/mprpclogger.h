#pragma once

#include <string>

#include "lockqueue.h"

#define LOG_INFO(logmsgFormat, ...)                       \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(INFO);                         \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
    } while (0)

#define LOG_ERROR(logmsgFormat, ...)                      \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(ERROR);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
    } while (0)

#define LOG_FATAL(logmsgFormat, ...)                      \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(FATAL);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
        exit(-1);                                         \
    } while (0)

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...)                      \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(DEBUG);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
    } while (0)
#else
#define LOG_DEBUG(logmsgFormat, ...)
#endif

// ??????????????????
enum LogLevel
{
    INFO,  // ????????????
    ERROR, // ????????????
    FATAL, // core??????
    DEBUG, // ????????????
};

// Mprpc???????????????????????????
class Logger
{
public:
    // ?????????????????????
    static Logger &GetInstance();
    // ??????????????????
    void SetLogLevel(LogLevel level);
    // ?????????
    void Log(std::string msg);

private:
    int logLevel_;                     // ??????????????????
    LockQueue<std::string> lockQueue_; // ??????????????????

    Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};
