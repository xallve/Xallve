#include "block.hpp"
#include <openssl/sha.h>
#include <sstream>

Block::Block(std::string data, std::string previousHash)
    : data(data), previousHash(previousHash), timestamp(std::time(nullptr)) {
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::string toHash = previousHash + std::to_string(timestamp) + data;
    unsigned char hashResult[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)toHash.c_str(), toHash.size(), hashResult);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << (int)hashResult[i];
    }
    return ss.str();
}

std::string Block::getHash() const {
    return hash;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::string Block::getData() const {
    return data;
}

std::time_t Block::getTimestamp() const {
    return timestamp;
}
