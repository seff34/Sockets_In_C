#include "logger.h"

logLevel_t logLevel = DEBUG;

/**
 * @brief  Debug Level Name
 * @param  [in] selectLogLevel
 * @return [const char*] Debug Level String
 */
static const char *debugLevelGetString(logLevel_t selectLogLevel)
{
    if (selectLogLevel <= ERROR)
        return "ERROR";
    else if (selectLogLevel <= WARNING)
        return "WARN";
    else if (selectLogLevel <= INFO)
        return "INFO";
    return "DEBG";
}

void logger(logLevel_t selectLogLevel, const char *format, ...)
{
    va_list va;
    va_start(va, format);

    if (selectLogLevel <= logLevel)
    {
        char timeBuf[30];
        time_t TIME = time(NULL);
        struct tm *timenow = gmtime(&TIME);
        strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %X", timenow);

        fprintf(stdout, "[%s]: %s ", debugLevelGetString(selectLogLevel), timeBuf);
        vfprintf(stdout, format, va);
        if (selectLogLevel == ERROR)
        {
            fprintf(stderr, "[%s]: %s ", debugLevelGetString(selectLogLevel), timeBuf);
            vfprintf(stderr, format, va);
        }
    }
    va_end(va);
    return;
}

void flogger(logLevel_t selectLogLevel, const char *format, ...)
{
    va_list va;
    va_start(va, format);

    if (selectLogLevel <= logLevel)
    {
        char filename[60];
        char timeBuf[30];
        time_t TIME = time(NULL);
        struct tm *timenow = gmtime(&TIME);

        strftime(filename, sizeof(filename), "deviceLogs/%Y_%m_%d_App.log", timenow);
        strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %X", timenow);
        FILE *file = fopen(filename, "a");
        fprintf(file, "[%s]: %s ", debugLevelGetString(selectLogLevel),timeBuf);

        vfprintf(file, format, va);
        va_end(va);
        fclose(file);
        return;
    }
    va_end(va);
    return;
}