#include "keypair.hpp"
#include <sodium.h>
#include <vector>
#include <string>
#include "libbase58.h"


namespace Xallve {

    Keypair::Keypair() {
        if (sodium_init() < 0) {
            throw SodiumInitializationException();
        }

        std::vector<uint8_t> publicKey(crypto_sign_PUBLICKEYBYTES);
        mPrivateKey.resize(crypto_sign_SECRETKEYBYTES);

        crypto_sign_keypair(publicKey.data(), mPrivateKey.data());
        mPubKey = PubKey(publicKey);
    }

    Keypair::Keypair(const std::vector<uint8_t>& byteArray) {
        if (byteArray.size() != crypto_sign_SECRETKEYBYTES) {
            throw InvalidKeypairSizeException();
        }

        std::vector<uint8_t> PrivateKey; 
        PrivateKey.assign(byteArray.begin(), byteArray.begin() + crypto_sign_SECRETKEYBYTES);

        std::vector<uint8_t> derivedPublicKey(crypto_sign_PUBLICKEYBYTES);
        if (crypto_sign_ed25519_sk_to_pk(derivedPublicKey.data(), PrivateKey.data()) != 0) {
            throw std::runtime_error("Failed to derive public key from private key");
        }

        if (!crypto_core_ed25519_is_valid_point(derivedPublicKey.data())) {
            throw PublicKeyIsNotOnCurve();
        }

        mPrivateKey.assign(PrivateKey.begin(), PrivateKey.begin() + crypto_sign_SECRETKEYBYTES);
        mPubKey = PubKey(derivedPublicKey);

    }

    Keypair::Keypair(const std::string& base58String) {
        std::vector<uint8_t> byteArray;
        size_t byteArraySize = crypto_sign_SECRETKEYBYTES;
        byteArray.resize(byteArraySize);
        if (!b58tobin(byteArray.data(), &byteArraySize, base58String.c_str(), base58String.size())) {
            throw Base58DecodeException();
        }
        byteArray.resize(byteArraySize);
        std::vector<uint8_t> derivedPublicKey(crypto_sign_PUBLICKEYBYTES);
        if (crypto_sign_ed25519_sk_to_pk(derivedPublicKey.data(), byteArray.data()) != 0) {
            throw std::runtime_error("Failed to derive public key from private key");
        }

        if (!crypto_core_ed25519_is_valid_point(derivedPublicKey.data())) {
            throw PublicKeyIsNotOnCurve();
        }

        mPrivateKey.assign(byteArray.begin(), byteArray.begin() + crypto_sign_SECRETKEYBYTES);
        mPubKey = PubKey(derivedPublicKey);
    }

    Keypair::Keypair(const Keypair& other) 
        : mPrivateKey(other.mPrivateKey), mPubKey(other.mPubKey) {}
    
    Keypair::Keypair(Keypair&& other) noexcept 
        : mPrivateKey(std::move(other.mPrivateKey)), mPubKey(std::move(other.mPubKey)) {}

    Keypair& Keypair::operator=(const Keypair& other) {
        if (this != &other) {
            mPrivateKey = other.mPrivateKey;
            mPubKey = other.mPubKey;
        }
        return *this;
    }


    Keypair& Keypair::operator=(Keypair&& other) noexcept {
        if (this != &other) {
            mPrivateKey = std::move(other.mPrivateKey);
            mPubKey = std::move(other.mPubKey);
        }
        return *this;
    }

    std::vector<uint8_t> Keypair::to_bytes() const {
        return mPrivateKey;
    }

    std::string Keypair::to_string() const {
        std::vector<uint8_t> byteArray = to_bytes();
        char b58[128];
        size_t b58_len = sizeof(b58);
        if (!b58enc(b58, &b58_len, byteArray.data(), byteArray.size())) {
            throw Base58EncodeException();
        }
        return std::string(b58);
    }

    PubKey Keypair::PublicKey() const {
        return mPubKey;
    }
    
} // namespace Xallve
