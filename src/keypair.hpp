#ifndef KEYPAIR_HPP
#define KEYPAIR_HPP

#include <sodium.h>
#include <vector>
#include <string>
#include "keypairerrors.cpp"
#include "pubkey.hpp"

namespace Xallve {
    // TODO Add validation support
    class Keypair {
    public:
        Keypair();                                              // Random keypair
        Keypair(const std::vector<uint8_t>& byteArray);         // Keypair from bytearray
        Keypair(const std::string& base58String);               // Keypair from base58 string

        // get keys
        std::vector<uint8_t> getPublicKey() const;
        std::vector<uint8_t> getPrivateKey() const;

        // --------
        std::vector<uint8_t> toByteArray() const;
        std::string toBase58String() const;

        bool isValidKeypair(const std::vector<uint8_t>& byteArray);
    
    private:
        std::vector<uint8_t> mPublicKey;
        std::vector<uint8_t> mPrivateKey;
    };
}

#endif // KEYPAIR_HPP
