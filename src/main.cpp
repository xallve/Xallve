#include "block.hpp"
#include <openssl/sha.h>
#include <iostream>

int main() {
    using namespace Xallve;

    // Create genesis block
    Block genesisBlock(nullptr);
    std::cout << "Genesis Block Hash: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", genesisBlock.getHash()[i]);
    std::cout << std::endl;

    // Add data to genesisBlock
    uint8_t data1[] = {0x01, 0x02, 0x03, 0x04};
    genesisBlock.addData(data1);
    std::cout << "Genesis Block Hash after adding data: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", genesisBlock.getHash()[i]);
    std::cout << std::endl;

    // Create second block
    Block secondBlock(&genesisBlock);
    uint8_t data2[] = {0x05, 0x06, 0x07, 0x08};
    secondBlock.addData(data2);
    std::cout << "Second Block Hash: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", secondBlock.getHash()[i]);
    std::cout << std::endl;

    return 0;
}