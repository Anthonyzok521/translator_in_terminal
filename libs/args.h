#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#define VERSION "1.1.0"
#include <iostream>
#include <vector>
#include <cstring>
#include "httplib.h"

using namespace std;
using namespace httplib;

class Args {
public:
    int argc;
    char** argv;

    Args(int argc, char** argv);
};

class Tlr {
private:
    vector<pair<string, string>> arguments;
    string input;
    string lang;
    string auth;
    string path;

    void validateArgsCount(int argc);
    void validateArgument(const string& arg, const string& nextArg, bool& flag, const string& errorMessage);
    void processArguments(Args args);
    void validateRemainingArguments(Args args);
    void validateFileExtension(string path);
    string readFile(string path);

public:
    Tlr(string auth);
    string verifyArgs(Args args);
    void printHelp();
    void printVersion();
    void translate();
};
