#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <ctime>

class Block {
public:
    Block(std::string data, std::string previousHash = "");

    std::string getHash() const;
    std::string getPreviousHash() const;
    std::string getData() const;
    std::time_t getTimestamp() const;

private:
    std::string previousHash;
    std::string data;
    std::time_t timestamp;
    std::string hash;

    std::string calculateHash() const;
};

#endif // BLOCK_HPP