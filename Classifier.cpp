// Classifier.cpp
#include "Classifier.h"

#include <fstream>
#include <iostream>

void Classifier::train(char* trainingFile)
{

    std::ifstream trainFile(trainingFile);
    if(trainFile.is_open() == false) {
        throw std::invalid_argument("Could not open a file in void Classifier::train(const DSString &trainingFile)");
    }

    char line[1024];
    while (trainFile.getline(line, 1024))
    {
        // Convert C string to DSString
        DSString lineStr(line);

        DSString sentiment = lineStr.split(',')[0];
        DSString tweetText = lineStr.split(',')[5];

        // Tokenize tweet
        std::vector<DSString> words = clean::Tokenize(tweetText); // tokenize does not remove ...

        // Update word sentiments
        for (auto &word : words)
        {
            if(wordSentiment.find(word) == wordSentiment.end()) {
                wordSentiment.emplace(word, 0);
            }

            if (sentiment[0] == '4')
            {
                wordSentiment[word]++;
            }
            else if (sentiment[0] == '0')
            {
                wordSentiment[word]--;
            }
        }
    }
    trainFile.close();
}

int Classifier::classify(const std::vector<DSString>& tweetWords)
{

    int positive = 0;
    int negative = 0;

    for (auto &word : tweetWords)
    {
        if (wordSentiment.count(word) > 0)
        {
            int sentiment = wordSentiment[word];
            if (sentiment > 0)
                positive += sentiment;
            else
                negative -= sentiment;
        }
    }

    if (positive > negative)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

void Classifier::test(char* testFilePath)
                      {

    std::ifstream testFile(testFilePath);
    if(testFile.is_open() == false) {
        throw std::invalid_argument("Could not open a file in void Classifier::train(const DSString &trainingFile)");
    }

    char line[1024];
    while (testFile.getline(line, 1024))
    {
        // Convert C string to DSString
        DSString lineStr(line);

        DSString id = lineStr.split(',')[0];
        DSString tweetText = lineStr.split(',')[4];

        // Tokenize tweet
        std::vector<DSString> words = clean::Tokenize(tweetText); // tokenize does not remove ...

        // Update word sentiments
        int guessVal = classify(words);
        guesses.emplace(id, guessVal);
    }
    testFile.close();
}

void Classifier::printToResultsFile(char * resultsFile) {
    std::ofstream resFile(resultsFile);
    for (auto &item : guesses)
    {
        resFile << item.second << ',' << item.first << std::endl;
    }
}

void Classifier::printToAccuracyFile(char * answersFile, char * accuracyFile) {
    std::ifstream ansFile(answersFile);
    char buffer[1000];
    int correctCount = 0;
    int total = 0;
    ansFile.getline(buffer, 1000);
    while(ansFile.getline(buffer, 1000, ',')) {
        int answer = buffer[0] - '0';
        ansFile.getline(buffer, 1000);
        DSString id = buffer;
        if (guesses[id] == answer)
        {
            correctCount++;
        }
        total++;
    }
    ansFile.close();
    ansFile.open(answersFile);
    std::ofstream accFile(accuracyFile);
    ansFile.getline(buffer, 1000);

    accFile << (double)correctCount / total << std::endl;
    while(ansFile.getline(buffer, 1000, ',')) {
        int answer = buffer[0] - '0';
        ansFile.getline(buffer, 1000);
        DSString id = buffer;
        accFile << guesses[id] << "," << answer << "," << id << std::endl;
    }
    

    accFile.close();
    ansFile.close();
}

