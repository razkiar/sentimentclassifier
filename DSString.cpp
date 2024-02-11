#include "DSString.h"
#include <stdexcept>

// Default Constructor
DSString::DSString()
{
    // Allocating memory for an empty string (only null character)
    data = new char[1];
    // Initializing the string with a null character
    data[0] = '\0';
    // Setting length of the string to 0 as it is empty
    len = 0;
}

// Constructor with a c-string parameter
DSString::DSString(const char *cstr)
{
    // Calculating length of the input c-string
    len = 0;
    while (cstr[len] != '\0')
    {
        len++;
    }

    // Allocating memory to store the string (including the null character)
    data = new char[len + 1];

    // Copying characters from the input c-string to the class string
    for (size_t i = 0; i < len; i++)
    {
        data[i] = cstr[i];
    }

    // Adding a null character at the end to terminate the string
    data[len] = '\0';
}

// Copy constructor: constructs a new string using an existing one
DSString::DSString(const DSString &source)
{
    // Copying length from the source string
    len = source.len;

    // Allocating memory for the new string (including the null character)
    data = new char[len + 1];

    // Copying characters from the source string
    for (size_t i = 0; i < len; i++)
    {
        data[i] = source.data[i];
    }

    // Terminating the string with a null character
    data[len] = '\0';
}

// Destructor: cleans up the memory when an object goes out of scope or is deleted
DSString::~DSString()
{
    // Deallocating memory used to store the string
    delete[] data;
}

// Assignment operator: assigns the value from the right-hand side operand to the left-hand side operand
DSString &DSString::operator=(const DSString &rhs)
{
    // Checking for self-assignment: if addresses of both sides are equal
    if (this != &rhs)
    {
        // Freeing memory occupied by the left-hand side string
        delete[] data;

        // Copying length from the right-hand side operand
        len = rhs.len;

        // Allocating memory for the new string data
        data = new char[len + 1];

        // Copying characters from the right-hand side operand
        for (size_t i = 0; i < len; i++)
        {
            data[i] = rhs.data[i];
        }

        // Adding a null character to terminate the string
        data[len] = '\0';
    }
    return *this;
}

// Length function: returns the length of the string
size_t DSString::length() const
{
    return len;
}

char& DSString::operator[](size_t index) {
    if(index >= len)
        throw std::out_of_range("Index out of bounds");
    return data[index];
}

DSString DSString::operator+(const DSString &rhs) const {
    // new string length will be both strings lengths combined
    size_t newLen = len + rhs.len;
    char *newData = new char[newLen + 1];

    // copy current string to new data
    for (size_t i = 0; i < len; ++i) {
        newData[i] = data[i];
    }

    // append rhs string to new data
    for (size_t i = 0; i < rhs.len; ++i) {
        newData[len + i] = rhs.data[i];
    }

    // null terminate new string
    newData[newLen] = '\0';

    DSString newStr(newData);
    delete[] newData;
    return newStr;
}

bool DSString::operator==(const DSString &rhs) const {
    if (len != rhs.len)
        return false;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i])
            return false;
    }
    return true;
}

bool DSString::operator<(const DSString &rhs) const {
    size_t smallestLen = len < rhs.len ? len : rhs.len;
    for (size_t i = 0; i < smallestLen; ++i) {
        if (data[i] < rhs.data[i])
            return true;
        else if(data[i] > rhs.data[i])
            return false;
    }
    // If all chars are equal to this point, shorter string is smaller
    if (len < rhs.len)
        return true;
    else
        return false;
}

char* DSString::c_str() const {
    return data;
}

std::ostream& operator<<(std::ostream &os, const DSString &str){
    for(size_t i = 0; i < str.len; i++)
        os << str.data[i];
    return os;
}

// Substring function: creates a substring starting from "start" position with "numChars" characters
DSString DSString::substring(size_t start, size_t numChars) const
{
    // Validating if the requested substring is within bounds
    if (start + numChars > len)
    {
        throw std::out_of_range("Invalid range for substring");
    }

    // Allocating memory for the substring (including the null character)
    char *subStr = new char[numChars + 1];

    // Copying characters from the original string to the substring
    for (size_t i = 0; i < numChars; i++)
    {
        subStr[i] = data[start + i];
    }

    // Terminating the substring with a null character
    subStr[numChars] = '\0';

    // Creating a DSString object to return
    DSString returnStr(subStr);
    // Freeing memory used for the substring c-string
    delete[] subStr;

    return returnStr;
}

// To Lower: creates a new string where all uppercase characters are converted to lowercase
DSString DSString::toLower() const
{
    // Creating a new string object to hold the lowercase string
    DSString lowerStr;

    // Copying length from the original string
    lowerStr.len = len;

    // Allocating memory for the lowercase string
    delete[] lowerStr.data;
    lowerStr.data = new char[len + 1];

    // Iterating through each character of the original string
    for (size_t i = 0; i < len; i++)
    {
        // If character is uppercase, convert to lowercase; else, keep it as is
        if (data[i] >= 'A' && data[i] <= 'Z')
        {
            lowerStr.data[i] = data[i] + ('a' - 'A');
        }
        else
        {
            lowerStr.data[i] = data[i];
        }
    }

    // Terminating the lowercase string with a null character
    lowerStr.data[len] = '\0';

    return lowerStr;
}

// Split: divides the string into substrings based on a delimiter and stores them into an array
std::vector<DSString> DSString::split(char delimiter) const
{
    // Counting the number of substrings that will be created after splitting
    size_t arraySize = 1;
    for (size_t i = 0; i < len; i++)
    {
        if (data[i] == delimiter)
        {
            arraySize++;
        }
    }

    // Allocating memory for the array of substrings
    std::vector<DSString> subStrs;

    // Initializing variables to keep track of starting position and index of the substring array
    size_t startPos = 0;
    size_t subStrIndex = 0;

    // Iterating through each character of the string
    for (size_t i = 0; i < len; i++)
    {
        // When a delimiter is found, create a substring from the last position to the delimiter
        if (data[i] == delimiter)
        {
            subStrs.push_back(this->substring(startPos, i - startPos));
            startPos = i + 1;
        }
    }

    // Adding the last substring after the last delimiter to the array
    subStrs.push_back(this->substring(startPos, len - startPos));
    return subStrs;
}

// Find function: returns the position of a substring inside the string, -1 if not found
int DSString::find(const DSString &subStr) const
{
    // Iterating through the original string
    for (size_t i = 0; i <= len - subStr.len; i++)
    {
        // Checking whether the substring matches with part of the original string starting from i
        bool match = true;
        for (size_t j = 0; j < subStr.len; j++)
        {
            if (data[i + j] != subStr.data[j])
            {
                match = false;
                break;
            }
        }
        // If a match was found, return the start position
        if (match)
        {
            return i;
        }
    }
    // Return -1 if no match was found
    return -1;
}

void DSString::removePunct() {
    char* temp = new char[len + 1];
    size_t j = 0;
    for (size_t i = 0; i < len ; i++)
    {
        char currentChar = data[i];
        if (std::isalpha(currentChar) || std::isspace(currentChar)) {
            temp[j] = currentChar;
            j++;
        }
    }
    temp[j] = '\0';
    delete[] data;
    data = temp;
    len = j;
}
