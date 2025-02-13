// translator_for_cmd_bash.cpp : Defines the entry point for the application.
//

#include "libs/translator_in_terminal.h"
#include "libs/message.model.h"

void verifyArgs(int argc) {
	if (!(argc > 1)) {
		throw runtime_error("To execute indicate by means of the argument:\n\n[NOTE]\nuse:\n\t--text, -t <\"your_text\">\nor:\n\t--file, -f <\"your_path_file.txt\">");
	}
}

int main(int argc, char** argv)
{
	try
	{

		verifyArgs(argc);
		Client cli("https://openrouter.ai");
		cli.set_default_headers({
			{ "Authorization", "Bearer API_KEY" }
			});
		auto res = cli.Post("/api/v1/chat/completions", R"({
			"model": "google/gemini-2.0-flash-thinking-exp:free",
			"messages" : [
				{
					"role": "user",
					"content" : [
						{
							"type": "text",
							"text" : "Hola! Puedes enviarme emojis?"
						},
					]
				}
			]
			})", "application/json");
		if (res && res->status == 200) {
			json jsonData = json::parse(res->body);

			ChatCompletion chatCompletion = parseChatCompletion(jsonData);

			chatCompletion.print();
		}
		else {
			cerr << "Error: " << res->status << endl;
		}
		/*json j = json::parse(res->body);
		const json& v = j["title"];

		cout << v;*/
		cout << "SUCCESS!";
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}

/*

API_KEY="YOUR_API_KEY"

curl \
  -X POST https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=${API_KEY} \
  -H 'Content-Type: application/json' \
  -d @<(echo '{
  "contents": [
	{
	  "role": "user",
	  "parts": [
		{
		  "text": "Manzana - inglés"
		}
	  ]
	},
	{
	  "role": "model",
	  "parts": [
		{
		  "text": "Apple \n"
		}
	  ]
	},
	{
	  "role": "user",
	  "parts": [
		{
		  "text": "Mañana iré al gimnasio - inglés"
		}
	  ]
	},
	{
	  "role": "model",
	  "parts": [
		{
		  "text": "I will go to the gym tomorrow. \n"
		}
	  ]
	},
	{
	  "role": "user",
	  "parts": [
		{
		  "text": "I'\''m a developer - spanish"
		}
	  ]
	},
	{
	  "role": "model",
	  "parts": [
		{
		  "text": "Soy un desarrollador. \n"
		}
	  ]
	},
	{
	  "role": "user",
	  "parts": [
		{
		  "text": "Tomorrow - es"
		}
	  ]
	},
	{
	  "role": "model",
	  "parts": [
		{
		  "text": "Mañana \n"
		}
	  ]
	},
	{
	  "role": "user",
	  "parts": [
		{
		  "text": "INSERT_INPUT_HERE"
		}
	  ]
	}
  ],
  "systemInstruction": {
	"role": "user",
	"parts": [
	  {
		"text": "Eres un traductor de idioma. Solo recibes una entrada y tu salida es traducirlo al idioma que se te indique. La sintaxis será la siguiente: frase - idioma y respondes con solo la traducción sin argumentar más nada ni decir otra cosa. Otra sintaxis también válida es la siguiente: frase - código del idioma. Los código de idioma son: en para inglés, es para español y otros que te agreguen."
	  }
	]
  },
  "generationConfig": {
	"temperature": 1,
	"topK": 64,
	"topP": 0.95,
	"maxOutputTokens": 8192,
	"responseMimeType": "text/plain"
  }
}')

*/