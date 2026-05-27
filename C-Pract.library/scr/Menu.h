#pragma once
#include "Warehouse.h"
#include <iostream>
#include <string>

class Menu {
private:
    Warehouse &warehouse;
    std::string filename;

    void printHeader();
    void printProduct(const Product &p);
    int getIntInput(const std::string &prompt, int min, int max);
    double getDoubleInput(const std::string &prompt, double min);
    std::string getStringInput(const std::string &prompt);
    void pressEnter();

    void addProduct();
    void editProduct();
    void deleteProduct();
    void searchProducts();
    void sortProducts();
    void showAnalytics();
    void saveData();

public:
    Menu(Warehouse &warehouse, const std::string &filename);
    void run();
};