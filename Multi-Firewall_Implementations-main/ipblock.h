#ifndef PACKET_BLOCKER_H
#define PACKET_BLOCKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
// #include <linux/if_ether.h>
// #include <linux/if_packet.h>

// Function declarations
void executeCommand(const std::string &command);
bool is_ip_blocked(const std::string &ip);
void blockIP(const std::string &ip);

#endif // PACKET_BLOCKER_H