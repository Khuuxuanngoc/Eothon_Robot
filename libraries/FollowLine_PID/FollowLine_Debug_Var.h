#pragma once

#define DEBUG_PRINT_LN(...)    this->p_Serial->println(__VA_ARGS__)
#define DEBUG_PRINT_T(...)    this->p_Serial->print(__VA_ARGS__); this->p_Serial->print("\t");

// #define DEBUG_RAW_QTR_VALUE_LN(...)     DEBUG_PRINT_LN(__VA_ARGS__)
// #define DEBUG_RAW_QTR_VALUE_T(...)      DEBUG_PRINT_T(__VA_ARGS__)

// #define DEBUG_RAW_PID_VALUE_LN(...)     DEBUG_PRINT_LN(__VA_ARGS__)
// #define DEBUG_RAW_PID_VALUE_T(...)      DEBUG_PRINT_T(__VA_ARGS__)

#define DEBUG_SERIAL_CMD_LN(...)     DEBUG_PRINT_LN(__VA_ARGS__)
#define DEBUG_SERIAL_CMD_T(...)      DEBUG_PRINT_T(__VA_ARGS__)


//=====================================================================

#ifndef DEBUG_RAW_QTR_VALUE_LN()
#define DEBUG_RAW_QTR_VALUE_LN(...)     
#define DEBUG_RAW_QTR_VALUE_T(...)
#endif

#ifndef DEBUG_RAW_PID_VALUE_LN()
#define DEBUG_RAW_PID_VALUE_LN(...)     
#define DEBUG_RAW_PID_VALUE_T(...)      
#endif

#ifndef DEBUG_SERIAL_CMD_LN()
#define DEBUG_SERIAL_CMD_LN(...)
#define DEBUG_SERIAL_CMD_T(...)
#endif