#include "block_data.hpp"

namespace Xallve {

BlockData::BlockData(const std::string& data) : data(data) {}

std::string BlockData::getData() const {
    return data;
}

void BlockData::setData(const std::string& data) {
    this->data = data;
}

}