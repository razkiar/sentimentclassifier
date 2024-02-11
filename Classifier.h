#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "tweet_utils.h"
#include "DSString.h"
#include <map>

class Classifier {
public:
  void train(char* trainingFile);
  int classify(const std::vector<DSString>& tweetWords);

  void test(char* testFile);
  void printToResultsFile(char* resultsFile);
  void printToAccuracyFile(char* answersFile, char* accuracyFile);

private:
  std::map<DSString, int> wordSentiment;
  std::map<DSString, int> guesses; // map from ID to guess (true == positive) (false == nagative)


};

#endif