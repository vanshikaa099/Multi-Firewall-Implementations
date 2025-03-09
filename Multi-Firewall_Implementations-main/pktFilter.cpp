#include "ipblock.h"
#include "ipunblock.h"
#include <string>
#include <sstream>
using std::string, std::cout, std::cin;

bool isValidIP(const std::string& ip) {
    std::string part;
    std::istringstream tokenStream(ip);
    int count = 0;

    while (std::getline(tokenStream, part, '.')) {
        if (part.empty() || part.length() > 3 || !std::all_of(part.begin(), part.end(), ::isdigit) || std::stoi(part) < 0 || std::stoi(part) > 255) {
            return false;
        }
        count++;
    }
    return count == 4;
}

int main() {
    std::string blacklistedIPsFile = "blacklist.txt";

    // Packet Filtering Firewall
    while(true){
        int choice;
        cout << "Press 1 to block IP\n";
        cout << "Press 2 to unblock IP\n";
        cout << "Press 101 to exit program\n";
        int choice;
        cin >> choice;

        string ip;
        string unip;

        switch(choice){
            case 1:
                cout << "Enter Src IP to block\n";
                if(isValidIP(ip)){
                    blockIP(ip);
                }
                else{
                    cout << "INVALID IP ENTERED\nTry Again\n";
                }
                break;
            case 2:
                cout << "Enter IP to unblock\n";
                if(isValidIP(unip)){
                    unblockIP(unip);
                }
                else{
                    cout << "INVALID IP ENTERED\nTry Again\n";
                }
                break;
            case 101:
                cout << "EXITING PROGRAM" << std::endl;
                exit(0);
        }
    }

    return 0;
}
