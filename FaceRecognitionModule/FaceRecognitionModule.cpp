#include <iostream>
#include <fstream>
#include "base64.h"

// #include <curlpp/cURLpp.hpp>
// #include <curlpp/Easy.hpp>
// #include <curlpp/Options.hpp>
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>

using namespace std;
// using namespace curlpp;

// void CreateSchema()
// {
// 	try
// 	{
// 		Cleanup myCleanup;
// 		Easy request;
// 		string endpoint = "http://localhost:8080/v1/schema";
// 		request.setOpt(new curlpp::options::Url(endpoint));

// 		list<string> header;
// 		header.push_back("Content-Type: application/json");
// 		request.setOpt(new curlpp::options::HttpHeader(header));

// 		request.setOpt(new curlpp::options::CustomRequest("POST"));

// 		string payload = R"({
//         "class": "ImageTest",
//         "description": "A test collection used for inserting and query images",
// 		"vectorIndexType": "hnsw",
//       	"vectorizer": "img2vec-neural",
// 		"moduleConfig": {
//           "img2vec-neural": {
//               "imageFields": [
//                   "image"
//               	]
//           	}
//       	},
//         "properties": [
//             {
//             "dataType": [
//                 "string"
//             ],
//             "description": "Name of the person in the image",
//             "name": "name"
//             },
//             {
//             "dataType": [
//                 "blob"
//             ],
//             "description": "The content of the image in base64",
//             "name": "image"
//             }
//         ]
//     	})";

// 		request.setOpt(new curlpp::options::PostFields(payload));
// 		request.setOpt(new curlpp::options::PostFieldSize(payload.length()));

// 		request.perform();
// 		cout << "All done" << endl << endl;

// 	}

// 	catch (curlpp::RuntimeError &e)
// 	{
// 		cout << e.what() << endl;
// 	}

// 	catch (curlpp::LogicError &e)
// 	{
// 		cout << e.what() << endl;
// 	}
// }

// void ImageToBase64(){

// 	string imagePath = "image_1.jpg";

// 	// Load the image
//     cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
//     if (image.empty()) {
//         std::cerr << "Error loading image: " << imagePath << std::endl;
//         return;
//     }

//     // Encode the image to a Base64 string
//     std::string encodedImage = encodeMat(image);

// 	// Dump the Base64 encoded string to a text file
//     std::ofstream outFile("encodedImage.txt");
//     if (!outFile) {
//         std::cerr << "Failed to open file for writing." << std::endl;
//         return;
//     }

//     outFile << encodedImage;
//     outFile.close();
//     std::cout << "Encoded image dumped to encodedImage.txt" << std::endl;

// 	return;

// }
int main(int argc, char *argv[])

{
	if (argc < 2)
	{
		std::cerr << "Include the path of an image as a parameter" << std::endl;
		return 1;
	}

	std::cout << argv[1] << std::endl;
	std::string imagePath = argv[1];

	std::string image_data = FileToBinary(imagePath);
	if (image_data.empty())
	{
		return 1;
	}

	std::string encodedImage = toBase64(image_data);

	std::string query = R"(
    {
      "query": "{
        Get {
          Images(nearImage: {
            image: \")" + encodedImage + R"(\"
          }) {
            image
          }
        }
      }"
    }
    )";

	std::cout << query << std::endl;

	return 0;
}