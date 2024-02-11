#include "tweet.h"
#include <cassert>
#include <iostream>

// Testing with a normal string
void test_constructor_with_normal_string() {
    DSString testStr("Hello, Twitter!");
    Tweet t(testStr);
    assert(t.getText() == testStr);
    std::cout << "Passed: Constructor with a normal string initializes string correctly\n";
}

// Testing with an empty string
void test_constructor_with_empty_string() {
    DSString testStr("");
    Tweet t(testStr);
    assert(t.getText() == testStr);
    std::cout << "Passed: Constructor with an empty string initializes string correctly\n";
}

// Testing with a long string
void test_constructor_with_long_string() {
    DSString testStr("This is a really long tweet that might even exceed the traditional length limit set by Twitter. Let's see how our Tweet class handles this.");
    Tweet t(testStr);
    assert(t.getText() == testStr);
    std::cout << "Passed: Constructor with a long string initializes string correctly\n";
}

// Testing the copy constructor
void test_copy_constructor() {
    DSString testStr("Testing copy constructor!");
    Tweet originalTweet(testStr);
    Tweet copiedTweet = originalTweet; // Using the copy constructor
    assert(copiedTweet.getText() == originalTweet.getText());
    std::cout << "Passed: Copy constructor copies string correctly\n";
}

// Testing the assignment operator
void test_assignment_operator() {
    DSString testStr1("First string");
    DSString testStr2("Second string");
    Tweet t1(testStr1);
    Tweet t2(testStr2);

    t2 = t1; // Using the assignment operator

    assert(t2.getText() == t1.getText());
    std::cout << "Passed: Assignment operator assigns string correctly\n";
}

// Testing getText() method
void test_getText_with_various_strings() {
    DSString testStr("Testing getText function");
    Tweet t(testStr);
    assert(t.getText() == testStr);
    std::cout << "Passed: getText() returns string correctly\n";
}

// Testing setText() method
void test_setText() {
    DSString initialStr("Initial string");
    DSString newStr("New string after setText");
    Tweet t(initialStr);

    t.setText(newStr); // Using the setText method
    assert(t.getText() == newStr);
    std::cout << "Passed: setText() modifies string correctly\n";
}

int main() {
    test_constructor_with_normal_string();
    test_constructor_with_empty_string();
    test_constructor_with_long_string();
    test_copy_constructor();
    test_assignment_operator();
    test_getText_with_various_strings();
    test_setText();

    std::cout << "All tests passed!\n";
    return 0;
}
