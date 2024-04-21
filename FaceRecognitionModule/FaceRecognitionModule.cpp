#include <iostream>
#include <fstream>
#include <curl/curl.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "base64.h"

using namespace std;

int main(int argc, char *argv[])
{

	// Take as second input the path of the image to compare
	if (argc < 2)
	{
		std::cerr << "Include the path of an image as a second parameter" << std::endl;
		return 1;
	}
	std::string imagePath = argv[1];

	// Image conversion to binary data
	std::string imageBinary = FileToBinary(imagePath);
	if (imageBinary.empty())
	{
		return 1;
	}

	// Image conversion from binary to base 64 encoding
	std::string encodedImage = toBase64(imageBinary);
	
	// JSON object creation with graphQL query in it
	std::string graphQLQuery = "{Get { Images(nearImage: { image:\"" + encodedImage +"\"}) { image _additional {certainty}} } }";

    rapidjson::Document jsonObj;
    jsonObj.SetObject();
	jsonObj.AddMember("query", rapidjson::Value(graphQLQuery.c_str(), jsonObj.GetAllocator()).Move() , jsonObj.GetAllocator());

    // Conversion from JSON object to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObj.Accept(writer);
    std::string jsonString = buffer.GetString();

	// Request creation using libcurl to retreive data from Weaviate
	CURL *request = curl_easy_init();
	curl_easy_setopt(request, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(request, CURLOPT_URL, "http://localhost:8080/v1/graphql");
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(request, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(request, CURLOPT_POSTFIELDS, jsonString.c_str());
	CURLcode ret = curl_easy_perform(request);

	return 0;
}