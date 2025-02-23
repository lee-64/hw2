#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"

/**
 * COMPLETE
 * 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */


class MyDataStore : public DataStore {
    public:
        ~MyDataStore() {}

        /**
         * Adds a product to the data store
         */
        void addProduct(Product* p) override;

        /**
         * Adds a user to the data store
         */
        void addUser(User* u) override;

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

        // Check if the username string is in users_
        bool usernameExists(std::string& username);

        // Add a Product object to the user's cart
        void addToCart(std::string& username, Product* product);

        // Fetch a user's cart
        std::queue<Product*> getUserCart(std::string& username);

        // If the Product is in stock
        bool inStock(Product* p);

        // If the user has enough money to buy the product
        bool sufficientBal(std::string& username, Product* p);

        // Convert a username to a User object
        User* usernameToUser(std::string& username);

        // Reset the user's old cart and replace it with their new cart (ie any unpurchased items left in the cart after BUYCART)
        void updateUserCart(std::string& username, std::queue<Product*> newCart);

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile) override;
    private:
        std::vector<User*> users_;
        std::map<std::string, std::queue<Product*>> usersCarts_;  // map of {username string: queue(product objects added to their cart (maintain FIFO)), ...}
        std::map<std::string, std::set<Product*>> keywordMap_;  // map of {keywords: set(product objects with that keyword), ...}
};

#endif
