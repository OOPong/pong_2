#include "csvLib.h"
// IMPLEMENTATION
void csvLib::parseCSV(const std::string& csvSource, std::vector<std::vector<std::string> >& lines)
{
	bool inQuote(false);
	bool newLine(false);
	std::string field;
	lines.clear();
	std::vector<std::string> line;

	std::string::const_iterator aChar = csvSource.begin();
	while (aChar != csvSource.end())
	{
		switch (*aChar)
		{
		case '"':
			newLine = false;
			inQuote = !inQuote;
			break;

		case delim:
			newLine = false;
			if (inQuote == true)
			{
				field += *aChar;
			}
			else
			{
				line.push_back(field);
				field.clear();
			}
			break;

		case '\n':
		case '\r':
			if (inQuote == true)
			{
				field += *aChar;
			}
			else
			{
				if (newLine == false)
				{
					line.push_back(field);
					lines.push_back(line);
					field.clear();
					line.clear();
					newLine = true;
				}
			}
			break;

		default:
			newLine = false;
			field.push_back(*aChar);
			break;
		}

		aChar++;
	}

	if (field.size())
		line.push_back(field);

	if (line.size())
		lines.push_back(line);
}
std::string csvLib::getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

void csvLib::printResults(std::vector<std::vector<std::string>>& results)
{
	long long i = 1;
	for (auto& row : results) {

		std::cout << "[" << i << "] ";

		for (auto& col : row) {

			std::cout << col;

			if (&col != &row.back()) {

				std::cout << " /// ";

			}
		}
		// leave the empty space in or else sometimes \n gets skipped
		// cannot flush buffer properly?
		std::cout << " " << std::endl;
		i++;
	}
}
void csvLib::writeCSV(std::string fileName, std::vector<std::vector<std::string> > lines)
{
	std::ofstream myfile;
	myfile.open(fileName, std::ios::out | std::ios::app);
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].size(); j++) {
			myfile << lines[i][j] << delim;
		}
		myfile << std::endl;
	}
	myfile.close();
}