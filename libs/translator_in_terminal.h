// translator_in_terminal.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#define VERSION "1.0.0"
#include "message.model.h"
#include <iostream>
#include <format>
#include <vector>
#include <cstring>
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
		{"-h", "--help"},
		{"-v", "--version"}
	};
	string input;
	string lang;
	string auth;

public:

	Tlr(string auth) : auth(auth) {}

	string verifyArgs(Args args) {
		if (args.argc == 2 && (args.argv[1] == arguments[3].first || args.argv[1] == arguments[3].second)) {
			printHelp();
			return "no-translate";
		}
		if (args.argc == 2 && (args.argv[1] == arguments[4].first || args.argv[1] == arguments[4].second)) {
			printVersion();
			return "no-translate";
		}
		if (args.argc < 5) {
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
		if (args.argc > 5) {
			throw runtime_error("Number of invalid arguments.");			
		}
		bool text_provided = false;
		bool file_provided = false;
		bool lang_provided = false;
		bool help_requested = false;

		for (int i = 1; i < args.argc; i++) {
			if (args.argv[i] == arguments[3].first || args.argv[i] == arguments[3].second) {
				help_requested = true;
				throw runtime_error("Cannot use -h, --help in this context.");
			}
			if (args.argv[i] == arguments[4].first || args.argv[i] == arguments[4].second) {
				throw runtime_error("Cannot use -v, --version in this context.");
			}
			if (args.argv[i] == arguments[0].first || args.argv[i] == arguments[0].second) {
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
			if (args.argv[i] == arguments[2].first || args.argv[i] == arguments[2].second) {

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
			if (args.argv[i] == arguments[1].first || args.argv[i] == arguments[1].second) {
				lang_provided = true;
				if (i + 1 < args.argc) {
					lang = args.argv[i + 1];
					i++;
				}
				else {
					throw runtime_error("Missing language after -l/--lang");
				}
			}			
		}

		int sizeArgs = args.argc;
		char** listArgs = args.argv;
		int j = 1;

		while(j < sizeArgs) {
			bool valid_arg = false;
			for (const auto& arg_pair : arguments) {
				 
				if ((listArgs[j] == arg_pair.first || listArgs[j] == arg_pair.second ||
					((listArgs[j] == arguments[0].first || listArgs[j] == arguments[0].second) && string(listArgs[j + 1]).find("-") == string::npos) ||
					((listArgs[j] == arguments[1].first || listArgs[j] == arguments[1].second) && string(listArgs[j + 1]).find("-") == string::npos) ||
					((listArgs[j] == arguments[2].first || listArgs[j] == arguments[2].second) && string(listArgs[j + 1]).find("-") == string::npos)) &&
					!help_requested
				) {
					valid_arg = true;
					if (sizeArgs != 3) {
						listArgs[1] = listArgs[3];
						listArgs[2] = listArgs[4];
						sizeArgs = 3;
						j = 1;
					}
					else {
						j = sizeArgs;
					}
					break;
				}
			}

			if (!valid_arg) {
				throw runtime_error(format("Invalid argument: {}\n\nExecute -h, --help for more information.", args.argv[j]));
			}
		}

		if (!lang_provided) {
			throw runtime_error("Language must be specified with --lang or -l.");
		}

		return "translate";
	}


	void printHelp() {
		cout << R"(
Usage: translate [options]

Options:
  -t, --text <"your_text">        Translate the given text.
  -f, --file <"your_path_file.txt">  Translate the content of the file.
  -L, --lang <"from_lang-to_lang" or "to_lang">  Language codes (e.g., "en-es", "en").
  -h, --help                      Display this help message.

Language Codes:
  es: Spanish       en: English       fr: French       de: German
  it: Italian       pt: Portuguese    ru: Russian      ja: Japanese
  zh: Chinese (Mandarin)  ar: Arabic  ko: Korean       sv: Swedish
  nl: Dutch         pl: Polish        hu: Hungarian    el: Greek
  vi: Vietnamese    th: Thai          id: Indonesian   bn: Bengali
  tr: Turkish       sw: Swahili       yo: Yoruba       zu: Zulu
  am: Amharic       nah: Nahuatl      qu: Quechua      myn: Maya
  hi: Hindi         fa: Persian       he: Hebrew       uk: Ukrainian
  cs: Czech

Examples:
  translate -t "Hola" -l "en"       Translate "Hola" to English.
  translate --file "myFile.txt" --lang "es-en"  Translate from Spanish to English.
)" << endl;
	}
	void printVersion() {
		cout << "Advanced Community - 2025" << endl;
		cout << "github - https://github.com/Anthonyzok521/translator_in_terminal.git"<<endl;
		cout << "project - translator_in_terminal" << endl;
		cout << "version - ";
		cout<<VERSION << endl;
	}

	void translate() {
		Client cli("https://openrouter.ai");
		cli.set_default_headers({
			{ "Authorization", this->auth }
			});
		auto res = cli.Post("/api/v1/chat/completions", R"({
			"model": "google/gemini-2.0-flash-thinking-exp:free",
			"messages": [
	{
	  "role": "system",
	  "content": "Eres un traductor de idioma. Solo recibes una entrada y tu salida es traducirlo al idioma que se te indique. La sintaxis será la siguiente: frase - idioma y respondes con solo la traducción sin argumentar más nada ni decir otra cosa. Otra sintaxis también válida es la siguiente: frase - código del idioma. Los código de idioma son: 'en' para inglés, 'es' para español sin las comillas y otros que te agreguen. Si no se te indica un texto o el idioma, responde en inglés diciendo que no se puede traducir. Recuerda siempre traducir y nunca responder directamente, si te hacen preguntas personales, solo traduce al idioma que se te indique. Eres asistente sólo para traducir palabras."
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
	  "content": ")" + input + ". " + lang + R"("
	}
	],
	"generationConfig": {
	  "temperature": 1,
	  "topK": 64,
	  "topP": 0.95,
	  "maxOutputTokens": 8192,
	  "responseMimeType": "text/plain"
	}
			  })", "application/json");
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
	  }
};