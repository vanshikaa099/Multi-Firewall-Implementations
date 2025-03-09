#include <iostream>
#include <unordered_set>
#include <fstream>
#include <pcap.h>
#include <string>
#include <netinet/ip.h>
#include "ipblock.h"

std::unordered_set<std::string> loadAllowlist(const std::string& filePath) {
    std::unordered_set<std::string> allowlist;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        allowlist.insert(line);
    }
    return allowlist;
}

void packetHandler(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet, const std::unordered_set<std::string>& allowlist) {
    struct ip* ipHeader = (struct ip*)(packet + 14);

    std::string srcIP = inet_ntoa(ipHeader->ip_src);

    if (allowlist.find(srcIP) != allowlist.end()) {
        std::cout << "Allowing packet from: " << srcIP << "\n";
    } else {
        std::cout << "Blocking packet from: " << srcIP << "\n";
        blockIP(srcIP);
    }
}
int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t* allDevs;

    std::string allowlistFile = "allowlist.txt";
    std::unordered_set<std::string> allowlist = loadAllowlist(allowlistFile);

    if (pcap_findalldevs(&allDevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << "\n";
        return 1;
    }

    pcap_t* handle = pcap_open_live(allDevs->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Error opening device: " << errbuf << "\n";
        return 1;
    }

    pcap_loop(handle, 0, (pcap_handler)packetHandler, (u_char*)&allowlist);

    // Cleanup
    pcap_close(handle);
    pcap_freealldevs(allDevs);
    return 0;
}

