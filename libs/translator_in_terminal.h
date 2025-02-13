// translator_for_cmd_bash.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "libs/message.model.h"
#include <iostream>
#include <format>
#include <vector>
#include "httplib.h"

using namespace std;
using namespace httplib;

class Args {
public:
	int argc;
	char** argv;

	Args(int argc, char** argv) {
		this->argc = argc;
		this->argv = argv;
	};
};

class Tlr {
private:
	vector<pair<string, string>> arguments = {
		{"-t", "--text"},
		{"-l", "--lang"},
		{"-f", "--file"},
		{"-v", "--version"}
	};
	string input;
	string output;
	string lang = "en-es";
	string auth;

public:

	Tlr(string auth, Args args) : auth(auth){
		this->verifyArgs(args);
	}

	void verifyArgs(Args args) {
		if (!(args.argc > 2)) {
			throw runtime_error(format(
				"To execute indicate by means of the argument:\n\n"
				"[NOTE]\n"
				"use:\n"
				"\t--text, -t <\"your_text\"> --lang, -l <\"from_lang-to_lang\">\n"
				"or:\n"
				"\t--file, -f <\"your_path_file.txt\"> --lang, -l <\"to_lang\">\n\n"
				"[CODES LANG]\n"
				"+ \"Spanish\", \"es\",\n"
				"+ \"English\", \"en\",\n"
				"+ \"French\", \"fr\",\n"
				"+ \"German\", \"de\",\n"
				"+ \"Italian\", \"it\",\n"
				"+ \"Portuguese\", \"pt\",\n"
				"+ \"Russian\", \"ru\",\n"
				"+ \"Japanese\", \"ja\",\n"
				"+ \"Chinese (Mandarin)\", \"zh\",\n"
				"+ \"Arabic\", \"ar\",\n"
				"+ \"Korean\", \"ko\",\n"
				"+ \"Swedish\", \"sv\",\n"
				"+ \"Dutch\", \"nl\",\n"
				"+ \"Polish\", \"pl\",\n"
				"+ \"Hungarian\", \"hu\",\n"
				"+ \"Greek\", \"el\",\n"
				"+ \"Vietnamese\", \"vi\",\n"
				"+ \"Thai\", \"th\",\n"
				"+ \"Indonesian\", \"id\",\n"
				"+ \"Bengali\", \"bn\",\n"
				"+ \"Turkish\", \"tr\",\n"
				"+ \"Swahili\", \"sw\",\n"
				"+ \"Yoruba\", \"yo\",\n"
				"+ \"Zulu\", \"zu\",\n"
				"+ \"Amharic\", \"am\",\n"
				"+ \"Nahuatl\", \"nah\",\n"
				"+ \"Quechua\", \"qu\",\n"
				"+ \"Maya\", \"myn\",\n"
				"+ \"Hindi\", \"hi\",\n"
				"+ \"Persian\", \"fa\",\n"
				"+ \"Hebrew\", \"he\",\n"
				"+ \"Ukrainian\", \"uk\",\n"
				"+ \"Czech\", \"cs\""
			));
		}
		
		bool text_provided = false;
		bool file_provided = false;
		bool lang_provided = false;
		bool help_requested = false;

		for (int i = 1; i < args.argc; i++) {
			for (const auto& arg_pair : arguments) {
				if (args.argv[i] == arg_pair.first || args.argv[i] == arg_pair.second) {
					if (arg_pair.first == "-h" || arg_pair.first == "--help") {
						printHelp();
						help_requested = true;
						return;
					}
					else if (arg_pair.first == "-t" || arg_pair.first == "--text") {
						if (file_provided) {
							throw runtime_error("Cannot use --text and --file together.");
						}
						text_provided = true;
						if (i + 1 < args.argc) {
							input = args.argv[i + 1];
							i++;
						}
						else {
							throw runtime_error("Missing text after -t/--text");
						}
					}
					else if (arg_pair.first == "-f" || arg_pair.first == "--file") {
						if (text_provided) {
							throw runtime_error("Cannot use --text and --file together.");
						}
						file_provided = true;
						if (i + 1 < args.argc) {
							input = args.argv[i + 1];
							i++;
						}
						else {
							throw runtime_error("Missing filename after -f/--file");
						}
					}
					else if (arg_pair.first == "-l" || arg_pair.first == "--lang") {
						lang_provided = true;
						if (i + 1 < args.argc) {
							lang = args.argv[i + 1];
							i++;
						}
						else {
							throw runtime_error("Missing language after -l/--lang");
						}
					}
					break;
				}
			}
		}

		for (int i = 1; i < args.argc; i++) {
			bool valid_arg = false;
			for (const auto& arg_pair : arguments) {
				if (args.argv[i] == arg_pair.first || args.argv[i] == arg_pair.second) {
					valid_arg = true;
					break;
				}
			}
			if (!valid_arg) {
				throw runtime_error(format("Invalid argument: {}\n\nExecute -h, --help for more information.", args.argv[i]));
			}
		}

		if (!lang_provided) {
			throw runtime_error("Language must be specified with --lang or -l.");
		}
	}


	static void printHelp() {
		cout << R"(
            Usage: translate [options]

            Options:
              -t, --text <"your_text">      Translate the given text.
              -f, --file <"your_path_file.txt"> Translate the content of the file.
              -l, --lang <"from_lang-to_lang" or "to_lang">  Language codes (e.g., "en-es", "en").
              -h, --help                   Display this help message.

            Language Codes:
              es: Spanish
              en: English
              fr: French
              de: German
              it: Italian
              pt: Portuguese
              ru: Russian
              ja: Japanese
              zh: Chinese (Mandarin)
              ar: Arabic
              ko: Korean
              sv: Swedish
              nl: Dutch
              pl: Polish
              hu: Hungarian
              el: Greek
              vi: Vietnamese
              th: Thai
              id: Indonesian
              bn: Bengali
              tr: Turkish
              sw: Swahili
              yo: Yoruba
              zu: Zulu
              am: Amharic
              nah: Nahuatl
              qu: Quechua
              myn: Maya
              hi: Hindi
              fa: Persian
              he: Hebrew
              uk: Ukrainian
              cs: Czech
              // Add more language codes as needed.

            Examples:
              translate -t "Hola" -l "en"       // Translate "Hola" to English.
              translate --file "myFile.txt" --lang "es-en" // Translate from Spanish to English
        )" << endl;
	}

	/*
	static void translate(string text) {
		Client cli("https://openrouter.ai");
		cli.set_default_headers({
			{ "Authorization", this->auth }
			});
		auto res = cli.Post("/api/v1/chat/completions", format(R"({
			"model": "google/gemini-2.0-flash-thinking-exp:free",
			"messages": [
	{
	  "role": "system",
	  "content": "Eres un traductor de idioma. Solo recibes una entrada y tu salida es traducirlo al idioma que se te indique. La sintaxis será la siguiente: frase - idioma y respondes con solo la traducción sin argumentar más nada ni decir otra cosa. Otra sintaxis también válida es la siguiente: frase - código del idioma. Los código de idioma son: en para inglés, es para español y otros que te agreguen."
	},
	{
	  "role": "user",
	  "content": "Manzana - inglés"
	},
	{
	  "role": "assistant",
	  "content": "Apple"
	},
	{
	  "role": "user",
	  "content": "Mañana iré al gimnasio - inglés"
	},
	{
	  "role": "assistant",
	  "content": "I will go to the gym tomorrow."
	},
	{
	  "role": "user",
	  "content": "I'm a developer - spanish"
	},
	{
	  "role": "assistant",
	  "content": "Soy un desarrollador."
	},
	{
	  "role": "user",
	  "content": "Tomorrow - es"
	},
	{
	  "role": "assistant",
	  "content": "Mañana"
	},
	{
	  "role": "user",
	  "content": "{}"
	}
  ],
  "generationConfig": {
	"temperature": 1,
	"topK": 64,
	"topP": 0.95,
	"maxOutputTokens": 8192,
	"responseMimeType": "text/plain"
  }
			})", text), "application/json");
		if (res && res->status == 200) {
			json jsonData = json::parse(res->body);

			ChatCompletion chatCompletion = parseChatCompletion(jsonData);

			//debug
			//chatCompletion.print();

			chatCompletion.choices[0].message.printMessage();
		}
		else {
			cerr << "Error: " << res->status << endl;
		}
		cout << "text: " << textOrPath;
		for (int i = 0; i < 3; i++) {
			cout << params[i];
		}
	}
	*/
};