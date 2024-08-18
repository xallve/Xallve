#include "timestamp.hpp"
#include <iomanip>
#include <sstream>

namespace Xallve {

Timestamp::Timestamp(std::time_t value) : value(value) {}

std::time_t Timestamp::getValue() const {
    return value;
}

std::string Timestamp::toString() const {
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&value), "%Y-%m-%d %H:%M:%S UTC");
    return ss.str();
}

bool Timestamp::operator==(const Timestamp& other) const {
    return value == other.value;
}

bool Timestamp::operator!=(const Timestamp& other) const {
    return value != other.value;
}

}
