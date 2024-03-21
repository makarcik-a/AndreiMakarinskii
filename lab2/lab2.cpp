#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 50;

enum class Genre {
    Classics,
    Novel,
    Detective,
    Fantasy,
    Horror,
    History
};

enum class ValidateData {
    Valid,
    InvalidTitle,
    InvalidPages,
    InvalidGenre
};

struct Book {
    array<char, MAX_SIZE> title;
    int pages;
    Genre genre;
};

struct DeserializationResult {
    bool success;
    Book value;
};

ValidateData validateBook(const Book& book) {
    if (book.title.empty()) {
        return ValidateData::InvalidTitle;
    }
    if (book.pages < 0) {
        return ValidateData::InvalidPages;
    }
    if (static_cast<int>(book.genre) < static_cast<int>(Genre::Classics) ||
        static_cast<int>(book.genre) > static_cast<int>(Genre::History)) {
        return ValidateData::InvalidGenre;
    }
    return ValidateData::Valid;
}

//Serialization
/*bool serializeTitle(const Book& book, ostream& os) {
    for (const char& c : book.title) {
        if (c == ',') {
            return false; // Проверяем наличие запятых в заголовке
        }
        os << c;
    }
    return true;
}

void serializePages(const Book& book, ostream& os) {
    os << book.pages;
}

void serializeGenre(const Book& book, ostream& os) {
    os << static_cast<int>(book.genre);
}*/

bool serializeBook(const Book& book, ostream& os) {
    ValidateData rezult = validateBook(book);
    switch (rezult)
    {
    case ValidateData::Valid:
        break;
    case ValidateData::InvalidTitle:
        cout << "Title is incorrect!";
        return false;
    case ValidateData::InvalidPages:
        cout << "Pages field is incorrect!";
        return false;
    case ValidateData::InvalidGenre:
        cout << "Genre field is incorrect!";
        return false;
    default:
        cout << "Something went wrong!";
        return false;
    }

    for (const char& c : book.title) {
        if (c == ',') {
            return false;
        }
        os << c;
    }

    os << ",";
    os << book.pages;
    os << ",";
    os << static_cast<int>(book.genre);
    os << "\n";

    return true;
}

//Deserialization
string deserializeTitle(istream& is) {
    string title;
    getline(is, title, ',');
    return title;
}

int deserializePages(istream& is) {
    string pageStr;
    getline(is, pageStr, ',');
    try {
        return stoi(pageStr);
    }
    catch (...) {
        return -1;
    }
}

Genre deserializeGenre(istream& is) {
    int genreInt;
    is >> genreInt;
    return static_cast<Genre>(genreInt);
}

bool deserializeBook(Book& book, istream& is) {
    string title = deserializeTitle(is);
    int pages = deserializePages(is);
    Genre genre = deserializeGenre(is);

    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!title.empty() && pages != -1 && static_cast<int>(genre) >= 0) {
        copy(title.begin(), title.end(), book.title.begin());
        book.pages = pages;
        book.genre = genre;
        return true;
    }
    else {
        return false;
    }

    return true;
}

string genreToString(Genre genre) {
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

int main() 
{
    Book book_1{
        "The Great Gatsby",
        180,
        Genre::Classics,
    };

    Book book_2{
        "The Hobbit",
        300,
        Genre::Fantasy,
    };

    Book book_3{
        "Murder on the Orient Express",
        256,
        Genre::Detective,
    };

    Book book_4{
        "Dracula",
        418,
        Genre::Horror,
    };

    Book book_5{
        "1984",
        328,
        Genre::Novel,
    };

    vector<Book> books;
    books.push_back(book_1);
    books.push_back(book_2);
    books.push_back(book_3);
    books.push_back(book_4);
    books.push_back(book_5);

    //Serialize fata in file
    ofstream file;
    file.open("books.txt");

    if (file.is_open()) {
        for (int i = 0; i < books.size(); i++) {
            if (!serializeBook(books[i], file)) {
                cout << "An error occuried during serialization!" << endl;
                return -1;
            }
        }

        file.close();
    }
    else {
        cout << "Unable to open file";
    }

    //Deserialize data in vector array "library"
    vector<Book> library;
    Book book_;

    ifstream file1;
    file1.open("books.txt");
    
    if (file1.is_open()) {
        while (deserializeBook(book_, file1)) {
            cout << "Book info:\tTitle: " << left << setw(50) << string(book_.title.data())
                << "Pages: " << setw(7) << book_.pages
                << "Genre: " << genreToString(book_.genre) << endl;
            library.push_back(book_);
        }
    }
    else {
        cout << "Unable to open file";
    }

    file1.close();

    //Change data and add new books
    if (!library.empty()) {
        library[0].pages = 1200;
    }

    Book book_6{
        "The Adventures of Sherlock Holmes",
        307,
        Genre::Detective,
    };

    Book book_7{
        "Harry Potter and the Philosopher's Stone",
        320,
        Genre::Fantasy,
    };

    library.push_back(book_6);
    library.push_back(book_7);

    //Serealize data again in file
    ofstream file2;
    file2.open("books.txt");

    if (file2.is_open()) {
        for (int i = 0; i < library.size(); i++) {
            if (!serializeBook(library[i], file2)) {
                cout << "An error occuried during serialization!" << endl;
                return -1;
            }
        }

        file2.close();
    }
    else {
        cout << "Unable to open file";
    }

    //Show changes in console
    ifstream file3;
    file3.open("books.txt");

    if (file3.is_open()) {
        cout << "\n\t\t\t\t\t-----Changes in file-----\n";
        while (deserializeBook(book_, file3)) {
            cout << "Book info:\tTitle: " << left << setw(50) << string(book_.title.data())
                << "Pages: " << setw(7) << book_.pages
                << "Genre: " << genreToString(book_.genre) << endl;
            library.push_back(book_);
        }
    }
    else {
        cout << "Unable to open file";
    }

    file3.close();

    return 0;
}
