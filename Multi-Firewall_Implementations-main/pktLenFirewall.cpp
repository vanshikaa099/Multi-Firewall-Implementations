#include <iostream>
#include <fstream>
#include <pcap.h>
#include <string>
#include <unordered_set>
#include "ipblock.h"

void packetHandler(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    // Block packets larger than 1000 bytes
    if (pkthdr->len > 1000) {
        struct ip* ipHeader = (struct ip*)(packet + 14);
        std::string srcIP = inet_ntoa(ipHeader->ip_src);
        
        blockIP(srcIP);

        std::ofstream blacklistFile("blacklist.txt", std::ios::app);
        if (blacklistFile.is_open()) {
            blacklistFile << srcIP << "\n";
            blacklistFile.close();
        }

        std::cout << "Blocked IP: " << srcIP << "\n";
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t* allDevs;

    if (pcap_findalldevs(&allDevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << "\n";
        return 1;
    }

    pcap_t* handle = pcap_open_live(allDevs->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Error opening device: " << errbuf << "\n";
        return 1;
    }

    pcap_loop(handle, 0, packetHandler, nullptr);

    pcap_close(handle);
    pcap_freealldevs(allDevs);
    return 0;
}
