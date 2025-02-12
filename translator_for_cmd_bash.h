// translator_for_cmd_bash.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "httplib.h"
using namespace std;
using namespace httplib;

class Translator {
private:
	string _params[3][2] = { {"-t", "--text"}, {"-l", "--language"}, {"-f","--file"} };

public:
	Translator(string textOrPath, string params[]) {
		cout << "text: "<<textOrPath;
		for (int i = 0; i < 3; i++) {
			cout << params[i];
		}
	}
};