#pragma once
#include <sstream>
#include <string>

class Book {
private:
    std::string id;
    std::string title;
    std::string author;
    std::string genre;
    int year;
    int copies;
    double price;

public:
    Book();
    Book(const std::string &id, const std::string &title, const std::string &author, const std::string &genre, int year, int copies, double price);

    std::string getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getYear() const;
    int getCopies() const;
    double getPrice() const;

    void setId(const std::string &id);
    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setGenre(const std::string &genre);
    void setYear(int year);
    void setCopies(int copies);
    void setPrice(double price);

    std::string toString() const;
    static Book fromString(const std::string &line);
    static bool validate(const Book &b);
};