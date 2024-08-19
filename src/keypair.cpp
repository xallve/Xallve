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

        mPrivateKey.assign(byteArray.begin(), byteArray.begin() + crypto_sign_SECRETKEYBYTES);
        mPublicKey.assign(byteArray.begin() + crypto_sign_PUBLICKEYBYTES, byteArray.end());

        std::vector<uint8_t> derivedPublicKey(crypto_sign_PUBLICKEYBYTES);
        if (crypto_sign_ed25519_sk_to_pk(derivedPublicKey.data(), mPrivateKey.data()) != 0) {
            throw std::runtime_error("Failed to derive public key from private key");
        }

        if (derivedPublicKey != mPublicKey) {
            throw PublicKeyMismatchException();
        }
    }

    Keypair::Keypair(const std::string& base58String) {
        std::vector<uint8_t> byteArray;
        size_t byteArraySize = crypto_sign_SECRETKEYBYTES;
        byteArray.resize(byteArraySize);
        if (!b58tobin(byteArray.data(), &byteArraySize, base58String.c_str(), base58String.size())) {
            throw Base58DecodeException();
        }
        byteArray.resize(byteArraySize);
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
