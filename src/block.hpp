#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <ctime>
#include <vector>

namespace Xallve {
    class Block {
    public:
        Block(Block* prevBlock);
        ~Block();
        uint8_t* getHash() const;
        std::vector<uint8_t*> getData() const;
        std::time_t getTimeStamp() const;
        void addData(uint8_t* data);
    private:
        void calculateHash();
        Block* mprevBlock;
        std::vector<uint8_t*> mData;                // Treat transactions as vector of byte arrays
        uint8_t* mHash;
        std::time_t mCreatedTS;

    };
} // namespace Xallve

#endif // BLOCK_HPP