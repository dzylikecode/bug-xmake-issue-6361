#include <serial/serial.h>
#include "serial_port.h"

extern char* copyString(const std::string& str);

SerialHandle serial_open(const char* port, uint32_t baudrate, uint32_t timeout) {
    try {
        serial::Serial* serial = new serial::Serial(port, baudrate, serial::Timeout::simpleTimeout(timeout));
        if (serial->isOpen()) {
            return (SerialHandle)serial;
        } else {
            delete serial;
            return nullptr;
        }
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void serial_close(SerialHandle handle) {
    if (handle) {
        serial::Serial* serial = (serial::Serial*)handle;
        serial->close();
        delete serial;
    }
}

PortInfo* list_ports(int* count) {
    std::vector<serial::PortInfo> ports = serial::list_ports();
    *count = ports.size();
    PortInfo* port_info = (PortInfo*)malloc(sizeof(PortInfo) * (*count));
    for (int i = 0; i < *count; ++i) {
        port_info[i].port = copyString(ports[i].port);
        port_info[i].description = copyString(ports[i].description);
        port_info[i].hardware_id = copyString(ports[i].hardware_id);
    }
    return port_info;
}

void free_port_info(PortInfo* port_info, int count) {
    for (int i = 0; i < count; ++i) {
        free(port_info[i].port);
        free(port_info[i].description);
        free(port_info[i].hardware_id);
    }
    free(port_info);
}