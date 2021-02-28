#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>


struct alias {
	std::string comment;
	std::string line;
};

std::vector<std::string> lines;
std::vector<alias> aliases;

int randomAlias(int maxNum) {
	srand((unsigned) time(NULL));
	return rand() % maxNum;
}

void parseFile() {
	std::string homePath = getenv("HOME");
	std::string bashrc = homePath + "/.bashrc";
  	std::ifstream file(bashrc);
  	
	std::string currentLine;
  	while (std::getline(file, currentLine)) {
    	lines.push_back(currentLine);
  	}
}

void makeTokens() {
	int lineCount = lines.size();
	for (int i = 0; i < lineCount; i++) {
		std::string firstLine = lines[i];
		std::string secondLine = lines[i+1];
		if (firstLine[0] == '#' && secondLine.substr(0,6) == "alias ") {
			alias newAlias;
			newAlias.comment = firstLine;
			newAlias.line = secondLine;
			aliases.push_back(newAlias);
		}
	}
}

void writeMessage(alias currentAlias) {
	std::string green = "\e[32m";
	std::string tab = "\t";
	std::cout << std::endl << tab << currentAlias.comment << std::endl;
	std::cout << tab << green << currentAlias.line << std::endl << std::endl;
}

int main() {
	parseFile();
	makeTokens();

	int aliasesSize = aliases.size();
	int randAlias = randomAlias(aliasesSize);
	alias currentAlias = aliases[randAlias];

	writeMessage(currentAlias);
}
