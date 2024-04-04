#include <iostream>
#include <array>
#include <string_view>
#include <string>
#include <cassert>

using namespace std;
const int MAX_SIZE = 50;

enum class SearchField {
    Title,
    Pages,
    Genre
};

enum class Genre {
    Classics,
    Novel,
    Detective,
    Fantasy,
    Horror,
    History
};

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

struct Book {
    array<char, MAX_SIZE> title;
    int pages;
    Genre genre;
};

struct BookNode {
    Book data;
    BookNode* next;

    BookNode(const Book& book) : data(book), next(nullptr) {}
};

struct FindNodeResult {
    BookNode* previous;
    BookNode* current;

    FindNodeResult(BookNode* prev, BookNode* curr) : previous(prev), current(curr) {}
};

struct BookList {
    BookNode* head;
    int size = 0;

    BookList() : head(nullptr) {}

    //insert new item at the end
    BookNode* insertAfter(BookNode* node, const Book& value) {
        BookNode* newNode = new BookNode(value);
        if (!node) // if node == nullptr, add new as first item
        { 
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = node->next;
            node->next = newNode;
        }
        return newNode;
    }

    //Remove after an item
    void removeAfter(BookNode* node) {
        if (!head) // check if list is empty
            return;

        if (!node) { // check if nullptr
            BookNode* temp = head;
            head = head->next;
            delete temp;
        }
        else if (node->next) {
            BookNode* temp = node->next;
            node->next = node->next->next;
            delete temp;
        }
    }

    // Find Node by any field
    FindNodeResult findByField(const std::array<char, MAX_SIZE>& searchValue, SearchField searchField) {
        BookNode* prev = nullptr;
        BookNode* current = head;

        while (current) {
            switch (searchField) {
            case SearchField::Title:
                if (current->data.title == searchValue)
                    return FindNodeResult(prev, current);
                break;
            case SearchField::Pages:
                if (current->data.pages == stoi(searchValue.data()))
                    return FindNodeResult(prev, current);
                break;
            case SearchField::Genre:
                if (genreToString(current->data.genre) == string(searchValue.data()))
                    return FindNodeResult(prev, current);
                break;
            }
            prev = current;
            current = current->next;
        }

        return FindNodeResult(nullptr, nullptr);
    }

    // Print list
    void printList() {
        BookNode* current = head;
        while (current) {
            cout << "Title: " << current->data.title.data() << ", Pages: " << current->data.pages << endl;
            current = current->next;
        }
    }
};

//Count nodes in a list
int countNodes(BookList* list) {
    int count = 0;
    BookNode* current = list->head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Check fot loops
void assertNoCycles(BookList* list) {
    int count = 0;
    BookNode* current = list->head;
    while (current) {
        count++;
        if (count > list->size) {
            assert(false && "Cycle detected in the linked list.");
        }
        current = current->next;
    }
    cout << "No cycles detected in this list." << endl;
}

void printSearchedResult(const FindNodeResult& result, const std::array<char, MAX_SIZE>& searchValue, SearchField searchField) {
    switch (searchField)
    {
    case SearchField::Title:
        if (result.current) {
            cout << "Book with title \"" << searchValue.data() << "\" has found." << endl;
            if (result.previous)
                cout << "Previous book is: \"" << result.previous->data.title.data() << "\"." << endl;
            else
                cout << "Previous book not found." << endl;
        }
        else
            cout << "Book with title \"" << searchValue.data() << "\" not found.";
        break;
    case SearchField::Pages:
        if (result.current) {
            cout << "Book with " << stoi(searchValue.data()) << " pages has found, Title: \"" << result.current->data.title.data() << "\"." << endl;
            if (result.previous)
                cout << "Previous book is: \"" << result.previous->data.title.data() << "\" with " << result.previous->data.pages << " pages." << endl;
            else
                cout << "Previous book not found." << endl;
        }
        else
            cout << "Book with " << stoi(searchValue.data()) << " pages not found.";
        break;
    case SearchField::Genre:
        if (result.current) {
            cout << "Book with genre \"" << searchValue.data() << "\" has found, Title: \"" << result.current->data.title.data() << "\"." << endl;
            if (result.previous)
                cout << "Previous book is: \"" << result.previous->data.title.data() << "\" with \"" << genreToString(result.previous->data.genre) << "\" genre." << endl;
            else
                cout << "Previous book not found." << endl;
        }
        else
            cout << "Book with genre \"" << searchValue.data() << "\" not found.";
        break;
    }
}

int main() 
{
    BookList library;

    Book book1 { "The Great Gatsby", 180, Genre::Classics };
    Book book2 { "The Hobbit", 300, Genre::Fantasy };
    Book book3 { "Murder on the Orient Express", 256, Genre::Detective };
    Book book4 { "Dracula", 418, Genre::Horror };
    Book book5 { "1984", 328, Genre::Novel };
    Book book6 { "The Adventures of Sherlock Holmes", 307, Genre::Detective };
    Book book7 { "Harry Potter and the Philosopher's Stone", 320, Genre::Fantasy };

    BookNode* lastNode = nullptr;

    library.insertAfter(lastNode, book1);
    library.insertAfter(lastNode, book2);
    library.insertAfter(lastNode, book3);
    library.insertAfter(lastNode, book4);
    library.insertAfter(lastNode, book5);
    library.insertAfter(lastNode, book6);
    library.insertAfter(lastNode, book7);

    library.size = countNodes(&library);
    library.printList();
    cout << "Size of list :" << library.size << endl;
    assertNoCycles(&library);

    cout << endl;
    
    SearchField field = SearchField::Title;
    array<char, MAX_SIZE> search = { "1984" };
    FindNodeResult result = library.findByField(search, field);
    printSearchedResult(result, search, field);

    cout << endl;

    field = SearchField::Pages;
    search = { "320" };
    result = library.findByField(search, field);
    printSearchedResult(result, search, field);

    cout << endl;

    field = SearchField::Genre;
    search = { "Horror" } ;
    result = library.findByField(search, field);
    printSearchedResult(result, search, field);

    cout << endl;

    library.removeAfter(nullptr);
    library.removeAfter(library.head);

    library.printList();
    library.size = countNodes(&library);
    cout << "Size of list :" << library.size << endl;
    assertNoCycles(&library);

    return 0;
}