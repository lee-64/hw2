#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include "movie.h"
#include "util.h"


Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) 
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}


Movie::~Movie() {}


std::set<std::string> Movie::keywords() const {
    std::set<std::string> keys;

    // Add product name
    std::set<std::string> nameKeys = parseStringToWords(name_);

    // Add the genre name
    std::set<std::string> genreKeys = parseStringToWords(genre_);
    keys = setUnion(nameKeys, genreKeys);  // Combine the two sets

    return keys;
}

std::string Movie::displayString() const {
    std::string output = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_)+ " " + std::to_string(qty_) + " left.";
    return output;
}

void Movie::dump(std::ostream& os) const {
    /*
    Example formatting:
        movie
        Hidden Figures DVD
        17.99
        1
        Drama
        PG
    */

    os << std::fixed << std::setprecision(2);
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

