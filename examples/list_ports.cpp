/**
 * @file list_port.cpp
 * @brief Example program to list all available serial ports
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "serial_port.h"
#include <fmt/core.h>

int main() {
  std::cout << "Listing available serial ports:\n";
  std::cout << "-------------------------------\n";
  
  int count = 0;
  PortInfo* ports = list_ports(&count);
  
  if (count == 0) {
    std::cout << "No serial ports found.\n";
  } else {
    std::cout << "Found " << count << " ports:\n\n";
    
    for (int i = 0; i < count; i++) {
      fmt::print("Port #{}:\n", i + 1);
      fmt::print("  Port: {}\n", ports[i].port ? ports[i].port : "N/A");
      fmt::print("  Description: {}\n", ports[i].description ? ports[i].description : "N/A");
      fmt::print("  Hardware ID: {}\n\n", ports[i].hardware_id ? ports[i].hardware_id : "N/A");
    }
  }
  
  // Free the allocated memory
  if (ports) {
    free_port_info(ports, count);
  }
  
  return 0;
}