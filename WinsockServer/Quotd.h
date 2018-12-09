#pragma once

#include "Server.h"

class Quotd
{

public:
	Quotd(std::string filename);

	std::string getRandomQuote();

private:
	std::vector<std::string> quotes;

};