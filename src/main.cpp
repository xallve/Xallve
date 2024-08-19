#include "keypair.hpp"
#include <iostream>

int main() {
    try {
        // Got this from Keypair().toBase58
        Xallve::Keypair keypair(std::string("46aD2N8MuSDc5nWNysFVYFkogEuaaUDuTRo216E5thYPM93YncGaxZ6GZUMcBiZtzHfn8SVkoSACa3Evq2D5mHTi"));
        std::vector<uint8_t> pub = keypair.getPublicKey();
        std::vector<uint8_t> priv = keypair.getPrivateKey();
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


    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}