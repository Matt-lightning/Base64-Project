#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <bitset>

class Base64{
    public:
    static void encode(const std::string& unencrypted_text, const std::string& filename);
    static void decode(const std::string& encrypted_text, const std::string& filename);
    static int padding(std::string filename);
    static bool isvalidinput(const std::string& filename);
    static bool isvalidcharacter(const std::bitset<8>& byte);
};

# endif 