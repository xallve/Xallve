#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "block_data.hpp"
#include "hash.hpp"
#include "timestamp.hpp"
#include <string>

namespace Xallve {
class Block {
public:
    Block(const BlockData& data, const Hash& previousHash = Hash());

    Hash getHash() const;
    Hash getPreviousHash() const;
    BlockData getData() const;
    Timestamp getTimestamp() const;


private:
    Hash previousHash;
    BlockData data;
    Timestamp timestamp;
    Hash hash;

    Hash calculateHash() const;
};
}
#endif // BLOCK_HPP