#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> tokens;
    std::string curToken;

    for(unsigned char c : rawWords) {
        // The character is a punctuation mark or a space
        if(std::ispunct(c) || std::isspace(c)) {
            // If we have an active current token
            if(!curToken.empty()) {
                std::string trimmed = trim(curToken);  // Strip any whitespace surrounding the token
                if(trimmed.length() >= 2) {  // Ensure that the token is at least 2 characters long
                    tokens.insert(trimmed);
                }
                curToken.clear();  // Reset the current token
            }

        }
        // Else, append that character to the current token
        else {
            curToken += c;
        }
    }

    // Add the leftover token (which exists when rawWords doesn't end in punctuation)
    if(!curToken.empty()) {
        std::string trimmed = trim(curToken);  // Strip any whitespace surrounding the token
        if(trimmed.length() >= 2) {
            tokens.insert(trimmed);
        }
    }

    return tokens;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
