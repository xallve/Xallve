#include "block.hpp"
#include <openssl/sha.h>
#include <sstream>

namespace Xallve {
Block::Block(const BlockData& data, const Hash& previousHash)
    : data(data), previousHash(previousHash), timestamp(Timestamp()) {
    hash = calculateHash();
}

Hash Block::calculateHash() const {
    std::string toHash = previousHash.getValue() + std::to_string(timestamp.getValue()) + data.getData();
    unsigned char hashResult[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)toHash.c_str(), toHash.size(), hashResult);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << (int)hashResult[i];
    }
    return Hash(ss.str());
}

Hash Block::getHash() const {
    return hash;
}

Hash Block::getPreviousHash() const {
    return previousHash;
}

BlockData Block::getData() const {
    return data;
}

Timestamp Block::getTimestamp() const {
    return timestamp;
}

}