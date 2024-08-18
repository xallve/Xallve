#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <ctime>
#include <string>

namespace Xallve {

class Timestamp {
public:
    Timestamp(std::time_t value = std::time(nullptr));

    std::time_t getValue() const;
    std::string toString() const;

    bool operator==(const Timestamp& other) const;
    bool operator!=(const Timestamp& other) const;

private:
    std::time_t value;
};

} 

#endif // TIMESTAMP_HPP