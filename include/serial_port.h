#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #define EXPORT __declspec(dllexport)
  #else
    #define EXPORT __declspec(dllimport)
  #endif
#elif defined(__GNUC__) && __GNUC__ >= 4
  #define EXPORT __attribute__((visibility("default")))
#else
  #define EXPORT
#endif

#define SERIAL_PORT_API EXPORT

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* SerialHandle;

SERIAL_PORT_API SerialHandle serial_open(const char* port, uint32_t baudrate, uint32_t timeout);

SERIAL_PORT_API void serial_close(SerialHandle handle);


typedef char* utf8Bytes;

/**
 * @struct PortInfo
 * @brief Information about a serial port
 */
typedef struct {
  /** Address of the serial port (this can be passed to the constructor of Serial). */
  utf8Bytes port;
  
  /** Human readable description of serial device if available. */
  utf8Bytes description;
  
  /** Hardware ID (e.g. VID:PID of USB serial devices) or "n/a" if not available. */
  utf8Bytes hardware_id;
} PortInfo;

SERIAL_PORT_API PortInfo* list_ports(int* count);
SERIAL_PORT_API void free_port_info(PortInfo* port_info, int count);

#ifdef __cplusplus
}
#endif
