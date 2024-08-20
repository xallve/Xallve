#include <stdexcept>

class KeypairException : public std::runtime_error {
public:
    explicit KeypairException(const std::string& message)
        : std::runtime_error(message) {}
};

class SodiumInitializationException : public KeypairException {
public:
    SodiumInitializationException()
        : KeypairException("Failed to initialize libsodium") {}
};

class InvalidKeypairSizeException : public KeypairException {
public:
    InvalidKeypairSizeException()
        : KeypairException("Invalid byte array size for Keypair") {}
};

class PublicKeyMismatchException : public KeypairException {
public:
    PublicKeyMismatchException()
        : KeypairException("Provided public key does not match the private key") {}
};

class Base58DecodeException : public KeypairException {
public:
    Base58DecodeException()
        : KeypairException("Invalid base58 string for Keypair") {}
};

class Base58EncodeException : public KeypairException {
public:
    Base58EncodeException()
        : KeypairException("Failed to encode Keypair to base58") {}
};

class PublicKeyIsNotOnCurve : public KeypairException {
public:
    PublicKeyIsNotOnCurve()
        : KeypairException("Derived Publickey is not on curve") {}
};