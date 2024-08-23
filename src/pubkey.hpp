#ifndef PUBKEY_HPP
#define PUBKEY_HPP

#include <string>
#include <vector>

#define PUBKEY_SIZE 32U


namespace Xallve {

    class PubKey {
    public:
        PubKey();
        PubKey(const PubKey& other);
        PubKey(PubKey&& other) noexcept;
        PubKey(const std::vector<uint8_t>& byteArray);         // Pubkey from bytearray
        PubKey(const std::string& base58String);               // PublicKey from base58 string

        std::vector<uint8_t> to_bytes() const;
        std::string to_string() const;

        PubKey& operator=(const std::vector<uint8_t>& byteArray);
        PubKey& operator=(const PubKey& other);
        PubKey& operator=(PubKey&& other) noexcept;

    private:
        std::vector<uint8_t> mPubKey;
    };
    

}

#endif // PUBKEY_HPP