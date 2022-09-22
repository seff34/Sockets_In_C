#ifndef __LOGGER__H
#define __LOGGER__H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef enum
{
    ERROR   = 0,
    WARNING = 1,
    INFO    = 2, 
    DEBUG   = 3, 
}logLevel_t; 

extern logLevel_t logLevel;


/**
 * @brief Logger by stdout
 * @param [in] selectLogLevel Log Level
 * @param [in] format Printf Format
 * @param  ... Argumans
 */
void logger(logLevel_t selectLogLevel, const char *format,...);

/**
 * @brief Logger by file
 * @param [in] selectLogLevel Log Level
 * @param [in] format Printf Format
 * @param  ... Argumans
 */
void flogger(logLevel_t selectLogLevel, const char *format,...);


#endif