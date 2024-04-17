#include "../base64.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    std::string imagesPath = "../images";

    for (const auto &file : fs::directory_iterator(imagesPath))
    {
        if (file.is_regular_file())
        {
            std::string filename = file.path().filename();
            std::cout << filename << std::endl;

            std::string image_data = FileToBinary("../images/person_1.jpg");
            if (image_data.empty())
            {
                return 1;
            }

            std::string encodedImage = toBase64(image_data);

            std::ofstream outFile("./test/base64_encodings/" + filename + "_code.txt");
            if (!outFile)
            {
                std::cerr << "Failed to open file for writing." << std::endl;
                return -1;
            }

            outFile << encodedImage;
            outFile.close();
            std::cout << "Encoded image dumped to encodedImage.txt" << std::endl;
        }
    }

    return 0;
}