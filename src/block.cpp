#include "block.hpp"

#include <string.h>
#include <openssl/sha.h>

namespace Xallve {

    Block::Block(Block* prevBlock)
        : mprevBlock(prevBlock), mData(), mCreatedTS(std::time(0)) {
        
        mHash = new uint8_t[SHA256_DIGEST_LENGTH];
        // Fill blockhash
        if (mprevBlock)
            memcpy(mHash, mprevBlock->getHash(), SHA256_DIGEST_LENGTH);
        else
            memset(mHash, 0, SHA256_DIGEST_LENGTH);

        calculateHash(); // Initial blockhash calculation
    }

    Block::~Block() {
        delete[] mHash;
    }

    void Block::calculateHash() {
        // Bufer to collect data to hash
        size_t total_size = SHA256_DIGEST_LENGTH + sizeof(mCreatedTS);

        for (const auto& data : mData) {
            total_size += sizeof(data);
        }

        std::vector<uint8_t> toHash(total_size);
        uint8_t* ptr = toHash.data();

        memcpy(ptr, mHash, SHA256_DIGEST_LENGTH);
        ptr += SHA256_DIGEST_LENGTH;

        memcpy(ptr, &mCreatedTS, sizeof(mCreatedTS));
        ptr += sizeof(mCreatedTS);

        for (const auto& data : mData) {
            memcpy(ptr, data, sizeof(data));
            ptr += sizeof(data);
        }
        
        // Write data to blockhash member
        SHA256(toHash.data(), total_size, mHash);
    }

    void Block::addData(uint8_t* data) {
        mData.push_back(data);
        calculateHash();
    }


    uint8_t* Block::getHash() const {
        return mHash;
    }

    std::vector<uint8_t*> Block::getData() const {
        return mData;
    }

    std::time_t Block::getTimeStamp() const {
        return mCreatedTS;
    }

} // namespace Xallve