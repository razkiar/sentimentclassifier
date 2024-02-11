#include <algorithm>
#include <cctype>
#include <fstream>
#include <set>
#include <vector>
#include "DSString.h"

namespace clean {
DSString Stemmer(const DSString& word);
DSString ProcessToken(DSString, const std::set<DSString>&);
std::set<DSString> LoadStopWords(char* fileName);
std::vector<DSString> Tokenize(DSString& text);
}  // namespace clean
