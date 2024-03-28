#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string_view>

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

ValidateData validateBook(const Book& book) {
    if (book.title.empty()) {
        return ValidateData::InvalidTitle;
    }
    else {
        for (const char& c : book.title) {
            if (c == ',') {
                return ValidateData::InvalidTitle;
            }
        }
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
bool serializeBook(const Book& book, ostream& os) {
    ValidateData rezult = validateBook(book);

    if (rezult != ValidateData::Valid) {
        cout << "Error: ";
        switch (rezult)
        {
        case ValidateData::Valid:
            break;
        case ValidateData::InvalidTitle:
            cout << "Title is incorrect!";
            break;
        case ValidateData::InvalidPages:
            cout << "Pages field is incorrect!";
            break;
        case ValidateData::InvalidGenre:
            cout << "Genre field is incorrect!";
            break;
        default:
            cout << "Something went wrong!";
            break;
        }
        cout << endl;
        return false;
    }
    string titleStr(book.title.data());
    os << titleStr;
    os << ",";
    os << book.pages;
    os << ",";
    os << static_cast<int>(book.genre);
    os << "\n";

    return true;
}

//Deserialization
string deserializeTitle(istream& is) {
    char titleBuffer[MAX_SIZE];
    is.get(titleBuffer, MAX_SIZE, ',');
    is.ignore(numeric_limits<streamsize>::max(), '\n');  //remove the rest of the line
    return string(titleBuffer);
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
    if (is.good()) {
        return static_cast<Genre>(genreInt);
    }
}

bool deserializeBook(Book& book, istream& is) {
    string title = deserializeTitle(is);
    int pages = deserializePages(is);
    Genre genre = deserializeGenre(is);

    //remove the rest of the line
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!title.empty() && pages != -1 && static_cast<int>(genre) >= 0) {
        if (title.size() <= book.title.size()) {
            copy(title.begin(), title.end(), book.title.begin());
        }
        else {
            return false;
        }
        book.pages = pages;
        book.genre = genre;
        return true;
    }
    else {
        return false;
    }

    return true;
}

string_view genreToString(Genre genre) {
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

void deserializeDataFromFile(const string& filename, vector<Book>& books) {
    Book book_;
    ifstream file;
    file.open(filename);

    if (file.is_open()) {
        while (deserializeBook(book_, file)) {
            books.push_back(book_);
        }
    }
    else {
        cout << "Unable to open file";
    }

    file.close();
}

void serealizeDataInFile(const string& filename, vector<Book> books) {
    ofstream file;
    file.open(filename);

    if (file.is_open()) {
        for (int i = 0; i < books.size(); i++) {
            if (!serializeBook(books[i], file)) {
                cout << "An error occuried during serialization!" << endl;
            }
        }

        file.close();
    }
    else {
        cout << "Unable to open file";
    }
}

void printFileData(vector<Book> books) {
    for (Book book : books) {
        cout << "Book info:  Title: " << left << setw(50) << string(book.title.data())
            << "Pages: " << setw(7) << book.pages
            << "Genre: " << genreToString(book.genre) << endl;
    }
}

int main()
{
    vector<Book> books = {
    {"The Great Gatsby", 180, Genre::Classics},
    {"The Hobbit", 300, Genre::Fantasy},
    {"Murder on the Orient Express", 256, Genre::Detective},
    {"Dracula", 418, Genre::Horror},
    {"1984", 328, Genre::Novel}
    };

    //Serialize data in file
    serealizeDataInFile("books.txt", books);

    //Deserialize data in vector array "books"
    deserializeDataFromFile("books.txt", books);
    printFileData(books);

    //Change data and add new books
    if (!books.empty()) {
        books[0].pages = 1200;
    }

    Book book_6{ "The Adventures of Sherlock Holmes", 307, Genre::Detective };
    Book book_7{ "Harry Potter and the Philosopher's Stone", 320, Genre::Fantasy };

    books.push_back(book_6);
    books.push_back(book_7);

    //Serealize data again in file
    serealizeDataInFile("books.txt", books);

    //Show changes in console
    deserializeDataFromFile("books.txt", books);
    cout << "\n\t\t\t\t\t-----Changes in file-----\n";
    printFileData(books);

    return 0;
}