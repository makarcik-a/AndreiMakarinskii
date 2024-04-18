#pragma once

#include <iostream>
#include <array>
#include <string_view>
#include <string>
#include <vector>
#include <iomanip>

const int MAX_SIZE = 50;

enum class Genre {
    Classics,
    Novel,
    Detective,
    Fantasy,
    Horror,
    History
};

struct Book {
    std::array<char, MAX_SIZE> title;
    int pages;
    Genre genre;
};

std::string_view genreToString(Genre genre) {
    switch (genre) {
    case Genre::Classics:
        return "Classics";
    case Genre::Novel:
        return "Novel";
    case Genre::Detective:
        return "Detective";
    case Genre::Fantasy:
        return "Fantasy";
    case Genre::Horror:
        return "Horror";
    case Genre::History:
        return "History";
    default:
        return "Unknown";
    }
}

void printData(std::vector<Book> books) {
    for (Book book : books) {
        std::cout << "Book info:  Title: " << std::left << std::setw(50) << std::string(book.title.data())
            << "Pages: " << std::setw(7) << book.pages
            << "Genre: " << genreToString(book.genre) << std::endl;
    }
}