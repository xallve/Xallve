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

        mPublicKey.resize(crypto_sign_PUBLICKEYBYTES);
        mPrivateKey.resize(crypto_sign_SECRETKEYBYTES);

        crypto_sign_keypair(mPublicKey.data(), mPrivateKey.data());
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
        mPublicKey.assign(PrivateKey.begin() + crypto_sign_PUBLICKEYBYTES, PrivateKey.end());


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
        mPublicKey.assign(byteArray.begin() + crypto_sign_PUBLICKEYBYTES, byteArray.end());
    }

    std::vector<uint8_t> Keypair::toByteArray() const {
        std::vector<uint8_t> byteArray(mPrivateKey);
        return byteArray;
    }

    std::string Keypair::toBase58String() const {
        std::vector<uint8_t> byteArray = toByteArray();
        char b58[128];
        size_t b58_len = sizeof(b58);
        if (!b58enc(b58, &b58_len, byteArray.data(), byteArray.size())) {
            throw Base58EncodeException();
        }
        return std::string(b58);
    }

    std::vector<uint8_t> Keypair::getPublicKey() const {
        return mPublicKey;
    }

    std::vector<uint8_t> Keypair::getPrivateKey() const {
        return mPrivateKey;
    }
    
} // namespace Xallve
