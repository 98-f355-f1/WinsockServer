#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Quotd
{

public:
	Quotd(std::string filename);

	std::string getRandomQuote();

private:
	std::vector<std::string> quotes;

};