#include "tweet_utils.h"
#include "porter2_stemmer.h"
#include <string>

// A simplified example of a stemmer function
DSString clean::Stemmer(const DSString& word) {
    std::string temp = word.c_str();
    Porter2Stemmer::stem(temp);
    return DSString(temp.c_str());
}

// A function to process and clean a token
DSString clean::ProcessToken(DSString token, const std::set<DSString>& stopWords) {
    // Remove punctuation
    token.removePunct();
    // Convert to lowercase

    token = token.toLower();
    // If it's a stop word, return an empty string
    if (stopWords.find(token) != stopWords.end()) {
        return "";
    }

    // Stemming
    return clean::Stemmer(token);
}

// Load stop words from a file
std::set<DSString> clean::LoadStopWords(char* fileName) {
    std::set<DSString> stopWords;
    std::ifstream file(fileName);
    char word[1000];

    while (file >> word) {
        stopWords.emplace(word);
    }

    return stopWords;
}

// Tokenize a text string into words
std::vector<DSString> clean::Tokenize(DSString& text) {
    // Load Stop Words
    std::set<DSString> stopWords = clean::LoadStopWords("path_to_file");  // replace "path_to_file" with your actual file path

    std::vector<DSString> tokens;

    char currentWord[text.length() + 1];
    size_t j = 0;
    for (size_t i = 0; i < text.length(); i++) {
        char currentChar = text[i];
        if (std::isspace(currentChar) && j > 0) {
            currentWord[j] = '\0';
            DSString toClean = currentWord;
            toClean = clean::ProcessToken(toClean, stopWords);
            tokens.push_back(toClean);
            j = 0;
        } else {
            currentWord[j] = currentChar;
            j++;
        }
    }
    if (j > 0) {
        currentWord[j] = '\0';
        tokens.push_back(currentWord);
    }

    return tokens;
}