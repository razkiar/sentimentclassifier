#include <iostream>
#include <vector>
#include <algorithm>
#include "DSString.h"
#include <cassert>  // For assert()
#include <vector>

int main()
{
    DSString myString = "Hello, World!";
    std::cout << myString << "\n";

    // this uses the one argument constructor in DSString and then the inherited operator=
    myString = "Good bye!";
    std::cout << myString << "\n";

    std::cout << "substr: " << myString.substring(5, 3) << "\n";

    DSString a = "test";
    DSString b = a;

    std::cout << std::boolalpha;
    std::cout << (a == b) << "\n";

    // use initialization list
    std::vector<DSString> strings = {
        DSString("bbb"),
        DSString("aaa"),
        DSString("ddd"),
        DSString("eee"),
        DSString("ccc")};

    // find strings
    for (const auto &s : strings)
        std::cout
                << s << "\n";

    std::cout << "found ddd: " << (std::find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << "\n";
    std::cout << "found zzz: " << (std::find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << "\n";

    // sorting using the STL
    std::sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        std::cout
            << s << "\n";

    // now we can do more efficient search using STL binary search
    std::cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << "\n";
    std::cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << "\n";

    // Additional tests:

    // Testing default constructor and length() method
    DSString emptyStr;
    assert(emptyStr.length() == 0 && "Failed: Length of default constructor");

    // Testing copy constructor
    DSString original = "Original";
    DSString copyConstructed(original);
    assert(copyConstructed == original && "Failed: Copy constructor or operator==");

    // Testing assignment operator
    DSString assigned;
    assigned = original;
    assert(assigned == original && "Failed: Assignment operator or operator==");

    // Testing toLower() method
    DSString mixedCase = "MiXeD";
    DSString lowerCase = mixedCase.toLower();
    assert(lowerCase == "mixed" && "Failed: toLower() method");

    // Testing length() method
    DSString lengthStr = "12345";
    assert(lengthStr.length() == 5 && "Failed: Length calculation");

    // Testing substring() method
    DSString subStr = lengthStr.substring(1, 3);
    assert(subStr == "234" && "Failed: Substring calculation");

    // Testing split() method
    DSString toSplit = "a,b,c,d,e";
    std::vector<DSString> splitStrs;
    splitStrs = toSplit.split(',');
    size_t arraySize = splitStrs.size();
    assert(arraySize == 5 && "Failed: Split array size calculation");
    assert(splitStrs[0] == "a" && splitStrs[1] == "b" && splitStrs[2] == "c" &&
           splitStrs[3] == "d" && splitStrs[4] == "e" && "Failed: Split string content");

    // Testing destruction and memory management
    {
        DSString toDestroy = "To be destroyed";
    }   // toDestroy goes out of scope here, no memory leaks should be present

    // Additional test for exception handling in substring() method
    bool exceptionCaught = false;
    DSString strForException = "Test String";
    try
    {
        strForException.substring(3, 20);  // This should be out of range
    }
    catch(const std::out_of_range&)
    {
        exceptionCaught = true;
    }
    assert(exceptionCaught && "Failed: Out of range exception for substring");

    // Testing behavior with empty string
    DSString empty = "";
    assert(empty.length() == 0 && "Failed: Length of empty string not zero");

    DSString testDummy = "I want to find this"; //added
    std::cout << testDummy.find("this") << std::endl;
    assert(testDummy.find("this") == 15 && "Failed: find test");

    std::cout << "All tests passed!" << std::endl;

    return 0;
}