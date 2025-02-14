// translator_in_terminal.cpp : Defines the entry point for the application.
//

#include "libs/translator_in_terminal.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

string file;
string getExecutablePath() {
	char path[1024];
#ifdef _WIN32
	GetModuleFileName(NULL, path, sizeof(path));
	file = "\\.env";
#else
	file = "/.env";
	ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
	if (count != -1) {
		path[count] = '\0';
	}
	else {
		return "";
	}
#endif
	string fullPath(path);
	size_t lastSlash = fullPath.find_last_of("\\/");
	return fullPath.substr(0, lastSlash);
}


unordered_map<string, string> loadEnv(const string& filePath) {
	unordered_map<string, string> envVars;
	ifstream file(filePath);

	if (!file.is_open()) {
		throw runtime_error(".env not found with your API_KEY (Gemini)");
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
		string dir = getExecutablePath();

		unordered_map<string, string> env = loadEnv(dir + file);

		string API_KEY = env["API_KEY"];
		string auth = "Bearer " + API_KEY;		

		Tlr *trl = new Tlr(auth);
		if (trl->verifyArgs(Args(argc, argv)) == "translate") {
			trl->translate();
		}

		delete trl;

	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}