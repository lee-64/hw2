#include "util.h"
#include "mydatastore.h"
#include <string>
#include <set>

// MyDataStore::~MyDataStore() {
//     delete users_;
// }

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p) {
    std::set<std::string> productKeywords = p->keywords();
    for(std::set<std::string>::iterator it = productKeywords.begin(); it != productKeywords.end(); ++it) {
        keywordMap_[convToLower(*it)].insert(p);
    }
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u) {
    users_.push_back(u);
    std::queue<Product*> cart;  // Initialize an empty cart for that user
    usersCarts_[u->getName()] = cart;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> results;
    std::set<Product*> resultsSet;

    if(terms.empty()) {
        return results;
    }


    // AND search
    if(type == 0) {
        for(size_t i=0; i < terms.size(); ++i) {
            std::string lowerTerm = convToLower(terms[i]);
            // If there's a keyword in our database for the current search term
            if(keywordMap_.find(lowerTerm) != keywordMap_.end()) {
                // Intersect the values (a set of Products) corresponding to that keyword with the result set to get the shared Products

                // When resultsSet is initially empty, we don't want to do a setIntersection on an empty set
                if(resultsSet.empty()) {
                    resultsSet = keywordMap_[lowerTerm];
                }
                else {
                    resultsSet = setIntersection(resultsSet, keywordMap_[lowerTerm]);
                }
            }
        }

    }

    // OR search
    else {
        for(size_t i=0; i < terms.size(); ++i) {
            std::string lowerTerm = convToLower(terms[i]);
            // If there's a keyword in our database for the current search term
            if(keywordMap_.find(lowerTerm) != keywordMap_.end()) {
                // Add the values (a set of Products) corresponding to that keyword to the result set

                // When resultsSet is initially empty, we don't want to do a setUnion on an empty set
                if(resultsSet.empty()) {
                    resultsSet = keywordMap_[lowerTerm];
                }
                else {
                    resultsSet = setUnion(resultsSet, keywordMap_[lowerTerm]);
                }
            }
        }
    }

    // Convert the resultsSet back into a vector
    results.assign(resultsSet.begin(), resultsSet.end());
    return results;
}


// Check if the username string is in users_
bool MyDataStore::usernameExists(std::string& username) {
    for(size_t i=0; i < users_.size(); ++i) {
        if(convToLower(users_[i]->getName()) == convToLower(username)) {
            return true;
        }
    }
    return false;
}


// Add a Product object to the user's cart
void MyDataStore::addToCart(std::string& username, Product* p) {
    usersCarts_[username].push(p);
}


// Fetch a user's cart
std::queue<Product*> MyDataStore::getUserCart(std::string& username) {
    return usersCarts_[username];;
}


// If the Product is in stock
bool MyDataStore::inStock(Product* p) {
    if(p->getQty() > 0) {
        return true;
    }
    return false;
}


// If the user has enough money to buy the product
bool MyDataStore::sufficientBal(std::string& username, Product* p) {
    for(size_t i=0; i < users_.size(); ++i) {
        if(users_[i]->getName() == username) {  // Username found
            if(users_[i]->getBalance() - p->getPrice() >= 0) {  // The user's balance - the price of the item is >= 0, ie they have enough money
                return true;
            }
        }
    }
    return false;
}

// Convert a username to a User object
User* MyDataStore::usernameToUser(std::string& username) {
    for(size_t i=0; i < users_.size(); ++i) {
        if(users_[i]->getName() == username) {  // Username found
            return users_[i];
        }
    }
    return nullptr;
}

// Reset the user's old cart and replace it with their new cart (ie any unpurchased items left in the cart after BUYCART)
void MyDataStore::updateUserCart(std::string& username, std::queue<Product*> newCart) {
    // usersCarts_[username] = std::queue<Product*>();  // Clear the old cart by replacing it with an empty queue

    usersCarts_[username] = newCart;

}


/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "DUMPING" << std::endl;

}