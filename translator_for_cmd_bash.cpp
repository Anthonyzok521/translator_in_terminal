// translator_for_cmd_bash.cpp : Defines the entry point for the application.
//

#include "translator_for_cmd_bash.h"

using namespace std;

void verifyArgs(int argc) {
	if (!(argc > 1)) {
		throw runtime_error("To execute indicate by means of the argument:\n\n[NOTE]\nuse:\n\t--text, -t <\"your_text\">\nor:\n\t--file, -f <\"your_path_file.txt\">");
	}
}

int main(int argc, char **argv)
{
	try
	{
		verifyArgs(argc);
		cout << "SUCCESS!";
	}
	catch (const runtime_error& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}