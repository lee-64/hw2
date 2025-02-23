#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> sharedSet;

    for(typename std::set<T>::iterator s1_it = s1.begin(); s1_it != s1.end(); ++s1_it) {  // n iterations
        // If the element is in s2 too
        if(s2.find(*s1_it) != s2.end()) {
            sharedSet.insert(*s1_it);
        }
    }
    //  O(n*log(n))
    return sharedSet;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    
    std::set<T> joinedSet = s1;
    // Since nothing will happen when inserting an element that already exists, we can just power through
    for(typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {  // n iterations
        joinedSet.insert(*it);  // Each insert takes O(log(m)) time
    }
    // O(n*log(n))
    return joinedSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
