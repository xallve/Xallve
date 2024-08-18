#ifndef BLOCK_DATA_HPP
#define BLOCK_DATA_HPP

#include <string>

namespace Xallve {

class BlockData {
public:
    BlockData(const std::string& data = "");

    std::string getData() const;
    void setData(const std::string& data);

    // Add methods to work with transactions, metadata here maybe
private:
    std::string data;
};

}

#endif // BLOCK_DATA_HPP