#include "ipunblock.h"
#include <cstdlib>
#include <fstream>

void executeCmd(const std::string &command) {
    int result = system(command.c_str());
    if (result == -1) {
        std::cerr << "Error executing command: " << command << std::endl;
    }
}

bool isBlocked(const std::string &ip) {
    std::string checkCommand = "iptables -C INPUT -s " + ip + " -j DROP";
    int result = system(checkCommand.c_str());
    return result == 0;
}

void unblockIP(const std::string &ip) {
    if (isBlocked(ip)) {
        std::string unblockCommand = "iptables -D INPUT -s " + ip + " -j DROP";
        std::cout << "Unblocking IP: " << ip << std::endl;
        executeCmd(unblockCommand);
    } else {
        std::cout << "IP: " << ip << " is not currently blocked." << std::endl;
    }
}
