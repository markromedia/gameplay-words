#include "../src/rest_handler.hpp"

#include "gameplay.h"
#include <curl/curl.h>

RestHandler* RestHandler::instance = NULL;

size_t write_data(char* buffer, size_t size, size_t nmemb, void *userp)
{
	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, buffer);
	return size * nmemb;
}

void RestHandler::Init()
{
	instance = new RestHandler;
}

RestHandler* RestHandler::get()
{
	return instance;
}

bool RestHandler::HasInternetConnection()
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_URL, "www.google.com");
		gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "connecting to google.com to test internet connection...\n");
		res = curl_easy_perform(curl);
		switch (res)
		{
		case CURLE_COULDNT_CONNECT:
		case CURLE_COULDNT_RESOLVE_HOST:
		case CURLE_COULDNT_RESOLVE_PROXY:
			gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "no internet connection detected...\n");
			return false;
			break;
		}

		gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "successully connected...\n");
		/* always cleanup */ 
		curl_easy_cleanup(curl);
		return true;
	}
}

void RestHandler::SubmitRoundLog( RoundLog* round_log )
{
	CURL *curl;
	CURLcode res;
	std::string post_body = round_log->ToString();

	curl = curl_easy_init();
	
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	curl_easy_setopt(curl, CURLOPT_URL, "http://ec2-23-20-180-177.compute-1.amazonaws.com:3000/rounds.json");

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_body);

	res = curl_easy_perform(curl);
	
	/* Check for errors */ 
	if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

	/* always cleanup */ 
	curl_easy_cleanup(curl);
}



