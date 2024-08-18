#include "hash.hpp"

namespace Xallve {

Hash::Hash(const std::string& value): value(value) {}

std::string Hash::getValue() const {
    return value;
}

void Hash::setValue(const std::string& value) {
    this->value = value;
}

bool Hash::operator==(const Hash& other) const {
        return value == other.value;
}

bool Hash::operator!=(const Hash& other) const {
    return value != other.value;
}

}