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
        Keypair(const Keypair& other);
        Keypair(Keypair&& other) noexcept;
        Keypair(const std::vector<uint8_t>& byteArray);         // Keypair from bytearray
        Keypair(const std::string& base58String);               // Keypair from base58 string

        // get keys
        PubKey PublicKey() const;

        // --------
        std::vector<uint8_t> to_bytes() const;                  
        std::string to_string() const;                          // to Base58

        Keypair& operator=(const Keypair& other);
        Keypair& operator=(Keypair&& other) noexcept;

        bool isValidKeypair(const std::vector<uint8_t>& byteArray);
    
    private:
        PubKey mPubKey;
        std::vector<uint8_t> mPrivateKey;
    };
}

#endif // KEYPAIR_HPP
