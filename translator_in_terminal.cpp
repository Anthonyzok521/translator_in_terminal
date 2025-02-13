// translator_for_cmd_bash.cpp : Defines the entry point for the application.
//

#include "libs/translator_in_terminal.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

unordered_map<string, string> loadEnv(const string& filePath) {
	unordered_map<string, string> envVars;
	ifstream file(filePath);

	if (!file.is_open()) {
		throw runtime_error(".env not found");
	}

	string line;
	while (getline(file, line)) {
		if (line.empty() || line[0] == '#') {
			continue;
		}

		size_t delimiterPos = line.find('=');
		if (delimiterPos != string::npos) {
			string key = line.substr(0, delimiterPos);
			string value = line.substr(delimiterPos + 1);
			envVars[key] = value;
		}
	}

	file.close();
	return envVars;
}

int main(int argc, char** argv)
{
	try
	{		
		unordered_map<string, string> env = loadEnv(".env");

		string API_KEY = env["API_KEY"];
		string auth = "Bearer " + API_KEY;		

		Tlr(auth, Args(argc, argv));
		Tlr::printHelp();
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}