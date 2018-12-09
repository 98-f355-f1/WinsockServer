#include "Quotd.h"

Quotd::Quotd(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		std::string line;
		std::string running;

		while (getline(file, line))
		{
			if (line != "%")
			{
				running = running + line + "\n";
			}
			else
			{
				quotes.push_back(running);
				running = "";
			}
		}
	}
}

std::string Quotd::getRandomQuote()
{
	int r = rand() % quotes.size() + 1;
	return quotes[r];
}