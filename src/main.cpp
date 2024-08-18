#include <iostream>
#include "block.hpp"
#include "block_data.hpp"
#include "hash.hpp"
#include "timestamp.hpp"

int main() {
    using namespace Xallve;

    BlockData genesisData("Genesis Block");
    Block genesisBlock(genesisData);
    std::cout << "Genesis Block Hash: " << genesisBlock.getHash().getValue() << std::endl;

    BlockData secondData("Second Block");
    Block secondBlock(secondData, genesisBlock.getHash());
    std::cout << "Second Block Hash: " << secondBlock.getHash().getValue() << std::endl;

    return 0;
}