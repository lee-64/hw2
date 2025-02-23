#include <iostream>
#include <string>
#include <set>
#include "clothing.h"
#include "util.h"


Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) 
    : Product(category, name, price, qty), size_(size), brand_(brand) {}


Clothing::~Clothing() {}


std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keys;

    // Add product name
    std::set<std::string> nameKeys = parseStringToWords(name_);

    // Add the brand name
    std::set<std::string> brandKeys = parseStringToWords(brand_);
    keys = setUnion(nameKeys, brandKeys);  // Combine the two sets

    return keys;
}

std::string Clothing::displayString() const {
    std::string output = name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_)+ " " + std::to_string(qty_) + " left.";
    return output;
}

void Clothing::dump(std::ostream& os) const {
    /*
    Example formatting:
        clothing
        Men's Fitted Shirt
        39.99
        25
        Medium
        J. Crew
    */

    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}

