#include <iostream>
#include <string>
#include <set>
#include "book.h"
#include "util.h"


Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) 
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys;

    // Add product name
    std::set<std::string> nameKeys = parseStringToWords(name_);

    // Add the author's name and the ISBN number
    std::set<std::string> authorKeys = parseStringToWords(author_);
    keys = setUnion(nameKeys, authorKeys);  // Combine the two sets

    keys.insert(isbn_);  // Do not parse ISBN number for punctuation/tokenization

    return keys;
}

std::string Book::displayString() const {
    std::string output = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_)+ " " + std::to_string(qty_) + " left.";
    return output;
}

void Book::dump(std::ostream& os) const {
    /*
    Example formatting:
        book
        Great Men and Women of Troy
        19.50
        5
        978-000000000-1
        Tommy Trojan
    */

    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}

