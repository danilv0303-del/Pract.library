#pragma once
#include "Library.h"
#include <iostream>
#include <string>

class Menu {
private:
    Library &library;
    std::string filename;

    void printHeader();
    void printBook(const Book &b);
    int getIntInput(const std::string &prompt, int min, int max);
    double getDoubleInput(const std::string &prompt, double min);
    std::string getStringInput(const std::string &prompt);
    void pressEnter();

    void addBook();
    void editBook();
    void deleteBook();
    void searchBooks();
    void sortBooks();
    void showAnalytics();
    void saveData();

public:
    Menu(Library &library, const std::string &filename);
    void run();
};