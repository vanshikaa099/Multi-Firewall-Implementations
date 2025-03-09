#include "ipblock.h"
#include <cstring>
#include <unistd.h>

void executeCommand(const std::string &command) {
    int result = system(command.c_str());
    if (result == -1) {
        std::cerr << "Error executing command: " << command << std::endl;
    }
}

bool is_ip_blocked(const std::string &ip) {
    std::string checkCommand = "iptables -C INPUT -s " + ip + " -j DROP";
    int result = system(checkCommand.c_str());
    return result == 0;
}

void blockIP(const std::string &ip) {
    if (!is_ip_blocked(ip)) {
        std::string blockCommand = "iptables -A INPUT -s " + ip + " -j DROP";
        std::cout << "Blocking IP: " << ip << std::endl;
        executeCommand(blockCommand);
    } else {
        std::cout << "IP: " << ip << " is already blocked." << std::endl;
    }
}