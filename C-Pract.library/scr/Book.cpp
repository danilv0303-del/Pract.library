#include "Book.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

Book::Book() : year(0), copies(0), price(0.0) {}

Book::Book(const std::string &id, const std::string &title, const std::string &author, const std::string &genre, int year, int copies, double price)
    : id(id), title(title), author(author), genre(genre), year(year), copies(copies), price(price) {}

std::string Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getGenre() const { return genre; }
int Book::getYear() const { return year; }
int Book::getCopies() const { return copies; }
double Book::getPrice() const { return price; }

void Book::setId(const std::string &newId) { id = newId; }
void Book::setTitle(const std::string &newTitle) { title = newTitle; }
void Book::setAuthor(const std::string &newAuthor) { author = newAuthor; }
void Book::setGenre(const std::string &newGenre) { genre = newGenre; }
void Book::setYear(int newYear) { year = newYear; }
void Book::setCopies(int newCopies) { copies = newCopies; }
void Book::setPrice(double newPrice) { price = newPrice; }

std::string Book::toString() const {
    return id + "," + title + "," + author + "," + genre + "," + std::to_string(year) + "," + std::to_string(copies) + "," + std::to_string(price);
}

Book Book::fromString(const std::string &line) {
    std::istringstream iss(line);
    std::string id, title, author, genre, yearStr, copiesStr, priceStr;

    if (!std::getline(iss, id, ',') ||
        !std::getline(iss, title, ',') ||
        !std::getline(iss, author, ',') ||
        !std::getline(iss, genre, ',') ||
        !std::getline(iss, yearStr, ',') ||
        !std::getline(iss, copiesStr, ',') ||
        !std::getline(iss, priceStr, ',')) {
        throw std::runtime_error("Invalid line format: " + line);
    }

    int year = std::stoi(yearStr);
    int copies = std::stoi(copiesStr);
    double price = std::stod(priceStr);

    return Book(id, title, author, genre, year, copies, price);
}

bool Book::validate(const Book &b) {
    if (b.id.empty() || b.title.empty() || b.author.empty() || b.genre.empty()) return false;
    if (b.year <= 0) return false;
    if (b.copies < 0) return false;
    if (b.price < 0) return false;
    return true;
}