#include "../libs/args.h"
#include "../libs/message.model.h"

Args::Args(int argc, char** argv) : argc(argc), argv(argv) {}

Tlr::Tlr(string auth) : auth(auth), arguments({
    {"-t", "--text"},
    {"-l", "--lang"},
    {"-f", "--file"},
    {"-h", "--help"},
    {"-v", "--version"}
}) {}

void Tlr::validateArgsCount(int argc) {
    if (argc < 5) {
        throw runtime_error(R"(
            To execute indicate by means of the argument:

            [NOTE]
            use:
                --text, -t <"your_text"> --lang, -l <"from_lang-to_lang">
            or:
                --file, -f <"your_path_file.txt"> --lang, -l <"to_lang">

            [CODES LANG]
            + "Spanish", "es",
            + "English", "en",
            + "French", "fr",
            + "German", "de",
            + "Italian", "it",
            + "Portuguese", "pt",
            + "Russian", "ru",
            + "Japanese", "ja",
            + "Chinese Mandarin", "zh",
            + "Arabic", "ar",
            + "Korean", "ko",
            + "Swedish", "sv",
            + "Dutch", "nl",
            + "Polish", "pl",
            + "Hungarian", "hu",
            + "Greek", "el",
            + "Vietnamese", "vi",
            + "Thai", "th",
            + "Indonesian", "id",
            + "Bengali", "bn",
            + "Turkish", "tr",
            + "Swahili", "sw",
            + "Yoruba", "yo",
            + "Zulu", "zu",
            + "Amharic", "am",
            + "Nahuatl", "nah",
            + "Quechua", "qu",
            + "Maya", "myn",
            + "Hindi", "hi",
            + "Persian", "fa",
            + "Hebrew", "he",
            + "Ukrainian", "uk",
            + "Czech", "cs"
        )");
    }
    if (argc > 5) {
        throw runtime_error("Number of invalid arguments.");
    }
}

void Tlr::validateArgument(const string& arg, const string& nextArg, bool& flag, const string& errorMessage) {
    if (flag) {
        throw runtime_error(errorMessage);
    }
    flag = true;
    if (nextArg.empty() || nextArg[0] == '-') {
        throw runtime_error("Missing value after " + arg);
    }
}

void Tlr::processArguments(Args args) {
    bool textProvided = false;
    bool fileProvided = false;
    bool langProvided = false;

    for (int i = 1; i < args.argc; i++) {
        string currentArg = args.argv[i];
        string nextArg = (i + 1 < args.argc) ? args.argv[i + 1] : "";

        if (currentArg == arguments[3].first || currentArg == arguments[3].second) {
            throw runtime_error("Cannot use -h, --help in this context.");
        }
        if (currentArg == arguments[4].first || currentArg == arguments[4].second) {
            throw runtime_error("Cannot use -v, --version in this context.");
        }
        if (currentArg == arguments[0].first || currentArg == arguments[0].second) {
            validateArgument(currentArg, nextArg, textProvided, "Cannot use --text and --file together.");
            input = nextArg;
            i++;
        }
        if (currentArg == arguments[2].first || currentArg == arguments[2].second) {
            validateArgument(currentArg, nextArg, fileProvided, "Cannot use --text and --file together.");
            input = nextArg;
            i++;
        }
        if (currentArg == arguments[1].first || currentArg == arguments[1].second) {
            validateArgument(currentArg, nextArg, langProvided, "Missing language after -l/--lang");
            lang = nextArg;
            i++;
        }
    }

    if (!langProvided) {
        throw runtime_error("Language must be specified with --lang or -l.");
    }
}

void Tlr::validateRemainingArguments(Args args) {
    int sizeArgs = args.argc; // Get the number of arguments
    char** listArgs = args.argv; // Get the list of arguments
    int j = 1; // Start from the first argument after the program name

    while (j < sizeArgs) {
        bool validArg = false; // Flag to check if the argument is valid
        for (const auto& arg_pair : arguments) {
            // Check if the current argument matches any of the valid argument pairs
            if ((listArgs[j] == arg_pair.first || listArgs[j] == arg_pair.second ||
                // Check if the next argument is not another flag for text, lang, or file arguments
                ((listArgs[j] == arguments[0].first || listArgs[j] == arguments[0].second) && string(listArgs[j + 1]).find("-") == string::npos) ||
                ((listArgs[j] == arguments[1].first || listArgs[j] == arguments[1].second) && string(listArgs[j + 1]).find("-") == string::npos) ||
                ((listArgs[j] == arguments[2].first || listArgs[j] == arguments[2].second) && string(listArgs[j + 1]).find("-") == string::npos))) {
                validArg = true; // Mark the argument as valid
                if (sizeArgs != 3) {
                    // If the number of arguments is not 3, adjust the list of arguments
                    listArgs[1] = listArgs[3];
                    listArgs[2] = listArgs[4];
                    sizeArgs = 3; // Set the number of arguments to 3
                    j = 1; // Reset the index to 1
                } else {
                    j = sizeArgs; // Set the index to the number of arguments
                }
                break; // Exit the loop as the argument is valid
            }
        }

        if (!validArg) {
            // If the argument is not valid, throw an error
            throw runtime_error("Invalid argument: " + string(args.argv[j]) + "\n\nExecute - h, --help for more information.");
        }
    }
}

string Tlr::verifyArgs(Args args) {
    if (args.argc == 2 && (args.argv[1] == arguments[3].first || args.argv[1] == arguments[3].second)) {
        printHelp();
        return "no-translate";
    }
    if (args.argc == 2 && (args.argv[1] == arguments[4].first || args.argv[1] == arguments[4].second)) {
        printVersion();
        return "no-translate";
    }

    validateArgsCount(args.argc);
    processArguments(args);
    validateRemainingArguments(args);

    return "translate";
}

void Tlr::printHelp() {
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

void Tlr::printVersion() {
    cout << "Advanced Community - 2025" << endl;
    cout << "Author: https://github.com/Anthonyzok521" << endl;
    cout << "GitHub: https://github.com/Advanced-Community/translator_in_terminal.git" << endl;
    cout << "Project: - translator_in_terminal" << endl;
    cout << "Command: translate" << endl;
    cout << "Version: " << VERSION << endl;
}

void Tlr::translate() {
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
        chatCompletion.choices[0].message.printMessage();
    } else {
        cerr << "Error: " << res->status << endl;
    }
}
