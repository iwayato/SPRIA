#include "base64.h"

// Base64 encoding function (Thanks Copilot)
std::string toBase64(const std::string &input)
{
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string encoded;
    size_t i = 0;

    while (i < input.length())
    {
        uint32_t octet_a = static_cast<uint8_t>(input[i++]);
        uint32_t octet_b = static_cast<uint8_t>(input[i++]);
        uint32_t octet_c = static_cast<uint8_t>(input[i++]);

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded += base64_chars[(triple >> 18) & 0x3F];
        encoded += base64_chars[(triple >> 12) & 0x3F];
        encoded += base64_chars[(triple >> 6) & 0x3F];
        encoded += base64_chars[triple & 0x3F];
    }

    // Handle padding
    size_t padding = input.length() % 3;
    if (padding > 0)
    {
        encoded[encoded.length() - padding] = '=';
        if (padding == 1)
            encoded[encoded.length() - 2] = '=';
    }

    return encoded;
}

//Also thanks to Copilot
std::string FileToBinary(const std::string &file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return "";
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}