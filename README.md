# Translator in Terminal

Translator in Terminal is a command-line tool written in C++ that allows you to translate text and files using the Gemini API. It is compatible with Windows and Linux.

## Prerequisites

- **Gemini API Key**: You need a Gemini API key to use this tool.
- **`.env` File**: You must create a `.env` file in the same directory as the executable with the following variable:
  ```plaintext
  API_KEY=your_gemini_api_key
  ```
  Replace `your_gemini_api_key` with your Gemini API key.

- **Environment Variable Setup (Windows)**:
  To make the executable accessible from anywhere, add the path to the executable as an environment variable named `TRANSLATOR_IN_TERMINAL_ROOT`.

  ```shell
  setx TRANSLATOR_IN_TERMINAL_ROOT "C:\path\to\executable"
  ```
  
- **Environment Variable Setup (Linux)**:
  To make the executable accessible from anywhere, add the path to the executable to your shell configuration file (e.g., `.bashrc`, `.zshrc`).

  ```bash
  export TRANSLATOR_IN_TERMINAL_ROOT="/path/to/executable"
  export PATH=$PATH:$TRANSLATOR_IN_TERMINAL_ROOT
  ```

  Then, reload the configuration file:

  ```bash
  source ~/.bashrc  # or source ~/.zshrc
  ```
```
## Configuration in CMD (Windows)

> [!NOTE]
> Use Unicode text to avoid issues with special characters.
```shell
chcp 65001
```

## Usage Examples

### Translate Text
```shell
$ translate -t "hello" -l "en-es"
hola
```

### Translate a File and Save Output
```shell
$ translate --text "Hello, who are you?" --lang "en-zh" > output.txt
$ cat output.txt
你好，你是谁？
```

### Translate File Content
> [!NOTE]
> Coming Soon
```shell
$ translate --file "input.txt" --lang "es-en"
```

## How to Use?

```plaintext
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
```

## Author
- [@Anthonyzok521](https://www.github.com/Anthonyzok521) - **Advanced Community**

## Contributions
If you would like to contribute to this project, you are welcome! Please open an issue or submit a pull request in the repository.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
