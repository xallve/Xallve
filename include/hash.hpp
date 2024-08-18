#ifndef HASH_HPP
#define HASH_HPP

#include <string>

namespace Xallve {

class Hash {
public:
    Hash(const std::string& value = "");

    std::string getValue() const;
    void setValue(const std::string& value);

    bool operator==(const Hash& other) const;
    bool operator!=(const Hash& other) const;
private:
    std::string value;
};

}

#endif // HASH_HPP