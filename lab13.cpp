#include <iostream>
#include <vector>
#include <string>

class Product {
protected:
    std::string name;
    double price;

public:
    Product(const std::string& n, double p) : name(n), price(p) {}
    virtual ~Product() = default;
    virtual double getFinalPrice() const = 0;
    std::string getName() const { return name; }
    double getPrice() const { return price; }
};

class Discountable {
public:
    virtual double applyDiscount(double price) const = 0;
    virtual ~Discountable() = default;
};

class Book : public Product, public Discountable {
public:
    Book(const std::string& n, double p) : Product(n, p) {}
    double applyDiscount(double price) const override { return price * 0.9; }
    double getFinalPrice() const override { return applyDiscount(price); }
};

class Pen : public Product, public Discountable {
public:
    Pen(const std::string& n, double p) : Product(n, p) {}
    double applyDiscount(double price) const override { return price > 5 ? price - 5 : price; }
    double getFinalPrice() const override { return applyDiscount(price); }
};

int main() {
    std::vector<Product*> products = {
        new Book("Book A", 100),
        new Book("Book B", 150),
        new Pen("Pen A", 10),
        new Pen("Pen B", 4)
    };

    for (const auto& product : products) {
        std::cout << "Name: " << product->getName()
                  << ", Base Price: " << product->getPrice()
                  << ", Final Price: " << product->getFinalPrice() << std::endl;
    }

    for (auto& product : products) delete product;
    return 0;
}
