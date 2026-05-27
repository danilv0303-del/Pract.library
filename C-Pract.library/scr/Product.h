#pragma once
#include <sstream>
#include <string>

class Product {
private:
    std::string id;
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    Product();
    Product(const std::string &id, const std::string &name, const std::string &category, double price, int quantity);

    std::string getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getQuantity() const;

    void setId(const std::string &id);
    void setName(const std::string &name);
    void setCategory(const std::string &category);
    void setPrice(double price);
    void setQuantity(int quantity);

    std::string toString() const;
    static Product fromString(const std::string &line);
    static bool validate(const Product &p);
};