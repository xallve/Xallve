#include "keypair.hpp"
#include <iostream>

int main() {
    try {
        Xallve::Keypair keypair;
        std::vector<uint8_t> pub = keypair.PubKey();
        std::vector<uint8_t> priv = keypair.to_bytes();
        std::cout << "Public: " << std::endl;
        for (auto b : pub) {
            std::cout << std::hex << (int)b;
        }
        std::cout << std::endl;

        std::cout << "Private: " << std::endl;
        for (auto b : priv) {
            std::cout << std::hex << (int)b;
        }
        std::cout << std::endl;
        std::string s = keypair.to_string();
        std::cout << s;


    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}