#pragma once

#include <string>
#include <vector>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

using namespace jsoncons;

class Message {
public:
    std::string role;
    std::string content;
    std::string refusal;

    Message() : role(""), content(""), refusal("") {}

    Message(const std::string& role, const std::string& content, const std::string& refusal)
        : role(role), content(content), refusal(refusal) {
    }

    void print() const {
        std::cout << "Role: " << role << "\n"
            << "Content: " << content << "\n"
            << "Refusal: " << (refusal.empty() ? "null" : refusal) << "\n";
    }
};

class Choice {
public:
    std::string logprobs;
    std::string finish_reason;
    std::string native_finish_reason;
    int index;
    Message message;

    Choice() : logprobs(""), finish_reason(""), native_finish_reason(""), index(0), message() {}

    Choice(const std::string& logprobs, const std::string& finish_reason,
        const std::string& native_finish_reason, int index, const Message& message)
        : logprobs(logprobs), finish_reason(finish_reason),
        native_finish_reason(native_finish_reason), index(index), message(message) {
    }

    void print() const {
        std::cout << "Finish Reason: " << finish_reason << "\n"
            << "Native Finish Reason: " << native_finish_reason << "\n"
            << "Index: " << index << "\n"
            << "Message:\n";
        message.print();
    }
};

class Usage {
public:
    int prompt_tokens;
    int completion_tokens;
    int total_tokens;

    Usage() : prompt_tokens(0), completion_tokens(0), total_tokens(0) {}

    Usage(int prompt_tokens, int completion_tokens, int total_tokens)
        : prompt_tokens(prompt_tokens), completion_tokens(completion_tokens), total_tokens(total_tokens) {
    }

    void print() const {
        std::cout << "Prompt Tokens: " << prompt_tokens << "\n"
            << "Completion Tokens: " << completion_tokens << "\n"
            << "Total Tokens: " << total_tokens << "\n";
    }
};

class ChatCompletion {
public:
    std::string id;
    std::string provider;
    std::string model;
    std::string object;
    int created;
    std::vector<Choice> choices;
    Usage usage;

    ChatCompletion() : id(""), provider(""), model(""), object(""), created(0), choices(), usage() {}

    void print() const {
        std::cout << "ID: " << id << "\n"
            << "Provider: " << provider << "\n"
            << "Model: " << model << "\n"
            << "Object: " << object << "\n"
            << "Created: " << created << "\n"
            << "Choices:\n";
        for (const auto& choice : choices) {
            choice.print();
            std::cout << "-------------------\n";
        }
        std::cout << "Usage:\n";
        usage.print();
    }
};

ChatCompletion parseChatCompletion(const json& jsonData) {
    ChatCompletion chatCompletion;

    chatCompletion.id = jsonData["id"].as<std::string>();
    chatCompletion.provider = jsonData["provider"].as<std::string>();
    chatCompletion.model = jsonData["model"].as<std::string>();
    chatCompletion.object = jsonData["object"].as<std::string>();
    chatCompletion.created = jsonData["created"].as<int>();


    for (const auto& choiceData : jsonData["choices"].array_range()) {
        Choice choice;
        choice.logprobs = choiceData["logprobs"].is_null() ? "" : choiceData["logprobs"].as<std::string>();
        choice.finish_reason = choiceData["finish_reason"].as<std::string>();
        choice.native_finish_reason = choiceData["native_finish_reason"].as<std::string>();
        choice.index = choiceData["index"].as<int>();

        // Parsear message
        const auto& messageData = choiceData["message"];
        choice.message.role = messageData["role"].as<std::string>();
        choice.message.content = messageData["content"].as<std::string>();
        choice.message.refusal = messageData["refusal"].is_null() ? "" : messageData["refusal"].as<std::string>();

        chatCompletion.choices.push_back(choice);
    }

    const auto& usageData = jsonData["usage"];
    chatCompletion.usage.prompt_tokens = usageData["prompt_tokens"].as<int>();
    chatCompletion.usage.completion_tokens = usageData["completion_tokens"].as<int>();
    chatCompletion.usage.total_tokens = usageData["total_tokens"].as<int>();

    return chatCompletion;
}