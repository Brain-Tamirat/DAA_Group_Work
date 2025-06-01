#include <iostream>
#include <string>

// Function to reverse a string
std::string reverseString(const std::string& str) {
    std::string reversedStr = str;
    int start = 0, end = str.length() - 1;

    while (start < end) {
        // Swap characters at start and end indices
        char temp = reversedStr[start];
        reversedStr[start] = reversedStr[end];
        reversedStr[end] = temp;

        // Move towards the center
        start++;
        end--;
    }

    return reversedStr;
}
//This is Dan Bab.
int main() {
    std::string input;  // Input string

    std::cout << "Enter a sentence (less than 260 characters): ";
    std::getline(std::cin, input);

    if (input.length() > 0) {
        std::string reversedInput = reverseString(input);
        std::cout << "Reversed String: " << reversedInput << std::endl;
    } else {
        std::cout << "No input provided." << std::endl;
    }

    return 0;
}
