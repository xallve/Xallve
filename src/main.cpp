#include <iostream>
#include "block.hpp"

int main() {
    Block genesisBlock("Genesis Block");
    std::cout << "Genesis Block Hash: " << genesisBlock.getHash() << std::endl;
    
    Block secondBlock("Second Block", genesisBlock.getHash());
    std::cout << "Second Block Hash: " << secondBlock.getHash() << std::endl;

    return 0;
}