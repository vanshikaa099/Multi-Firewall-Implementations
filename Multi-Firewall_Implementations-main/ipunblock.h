#ifndef UNBLOCKER_H
#define UNBLOCKER_H

#include <iostream>
#include <unordered_set>
#include <string>

// Function declarations
void executeCmd(const std::string &command);
bool isBlocked(const std::string &ip);
void unblockIP(const std::string &ip);

#endif
