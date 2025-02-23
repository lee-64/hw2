#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <set>
#include "product.h"

class Book : public Product {
    public:
        Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
        ~Book();

        std::set<std::string> keywords() const override;

        std::string displayString() const override;

        void dump(std::ostream& os) const override;

    private:
        std::string isbn_;
        std::string author_;
};
#endif
