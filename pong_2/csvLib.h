#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <cerrno>
#include <iostream>
const char delim = ',';

//DEFINITION
class csvLib
{
public:
	static void parseCSV(const std::string& csvSource, std::vector<std::vector<std::string> >& lines);
	static std::string getFileContents(const char* filename);
	static void printResults(std::vector<std::vector<std::string> >& results);
	static void writeCSV(std::string fileName, std::vector<std::vector<std::string>> lines);
};


