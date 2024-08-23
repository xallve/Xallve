#include <cstdint>
#include <stdexcept>
#include "pubkey.hpp"

namespace Xallve {
    PubKey::PubKey(const PubKey& other)
        : mPubKey(other.mPubKey) {}
    
    PubKey::PubKey(PubKey&& other)
        :mPubKey(std::move(other.mPubKey)) {}

    PubKey::PubKey(const std::vector<uint8_t>& byteArray) {
        if (byteArray.size() != PUBKEY_SIZE) {
            throw std::invalid_argument("Invalid byte array size for PubKey");
        }
        mPubKey = byteArray;
    }

    PubKey::PubKey(const std::string& base58String) {
        
    }

    PubKey& PubKey::operator=(const std::vector<uint8_t>& byteArray) {
        if (byteArray.size() != PUBKEY_SIZE) {
            throw std::invalid_argument("Invalid key size");
        }
        mPubKey = byteArray;
        return *this;
    }

    PubKey& PubKey::operator=(const PubKey& other) {
        if (this != &other) {
            mPubKey = other.mPubKey;
        }
        return *this;
    }

    PubKey& PubKey::operator=(PubKey&& other) noexcept {
        if (this != &other) {
            mPubKey = std::move(other.mPubKey);
        }
        return *this;
    }

    std::vector<uint8_t> PubKey::to_bytes() const {
        return mPubKey;
    }

}