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
    BookNode* prev;
    BookNode* next;

    BookNode(const Book& book) : data(book), prev(nullptr), next(nullptr) {}
};

struct FindNodeResult {
    BookNode* previous;
    BookNode* current;

    FindNodeResult(BookNode* prev, BookNode* curr) : previous(prev), current(curr) {}
};

struct BookList {
    BookNode* head;
    BookNode* tail;
    int size = 0;

    BookList() : head(nullptr), tail(nullptr) {}

    //insert new item at the end
    BookNode* insertAfter(BookNode* node, const Book& value) {
        BookNode* newNode = new BookNode(value);
        if (!node) //if node == nullptr - insert at start of the list
        {
            if (!head) //if head == nullptr - list is empty
            { 
                head = newNode;
                tail = newNode;
            }
            else 
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }
        else //insert after node
        {
            newNode->next = node->next;
            if (node->next)
                node->next->prev = newNode;
            node->next = newNode;
            newNode->prev = node;
            if (node == tail)
                tail = newNode;
        }
        size++;
        return newNode;
    }

    //Remove after an item
    void removeAfter(BookNode* node) {
        if (!head)
            return;

        if (!node) //if node == nullptr - delete first item
        {
            BookNode* temp = head;
            head = head->next;
            if (head)
                head->prev = nullptr;
            if (temp == tail)
                tail = nullptr;
            delete temp;
        }
        else if (node->next) 
        {
            BookNode* temp = node->next;
            node->next = node->next->next;
            if (node->next)
                node->next->prev = node;
            if (temp == tail)
                tail = node;
            delete temp;
        }
        size--;
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
            cout << "Title: " << current->data.title.data() << ", Pages: " << current->data.pages << ", Genre: " << genreToString(current->data.genre) << endl;
            current = current->next;
        }
    }
};

// Check for loops
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
    if (result.current) {
        cout << "Book with criterion \"" << searchValue.data() << "\" has been found." << endl;
        if (result.previous)
            cout << "Previous book is: \"" << result.previous->data.title.data() << "\"." << endl;
        else
            cout << "Previous book not found." << endl;
    }
    else
        cout << "Book with criterion \"" << searchValue.data() << "\" not found.";
}

int main() {
    BookList library;

    Book book1{ "The Great Gatsby", 180, Genre::Classics };
    Book book2{ "The Hobbit", 300, Genre::Fantasy };
    Book book3{ "Murder on the Orient Express", 256, Genre::Detective };
    Book book4{ "Dracula", 418, Genre::Horror };
    Book book5{ "1984", 328, Genre::Novel };
    Book book6{ "The Adventures of Sherlock Holmes", 307, Genre::Detective };
    Book book7{ "Harry Potter and the Philosopher's Stone", 320, Genre::Fantasy };

    BookNode* lastNode = nullptr;

    lastNode = library.insertAfter(lastNode, book1);
    lastNode = library.insertAfter(lastNode, book2);
    lastNode = library.insertAfter(lastNode, book3);
    lastNode = library.insertAfter(lastNode, book4);
    lastNode = library.insertAfter(lastNode, book5);
    lastNode = library.insertAfter(lastNode, book6);
    lastNode = library.insertAfter(lastNode, book7);

    library.printList();
    cout << "Size of list: " << library.size << endl;
    assertNoCycles(&library);

    cout << endl;

    {
        SearchField field = SearchField::Title;
        array<char, MAX_SIZE> search = { "1984" };
        FindNodeResult result = library.findByField(search, field);
        printSearchedResult(result, search, field);
    }

    cout << endl;

    {
        SearchField field = SearchField::Pages;
        array<char, MAX_SIZE> search = { "320" };
        FindNodeResult result = library.findByField(search, field);
        printSearchedResult(result, search, field);
    }

    cout << endl;

    {
        SearchField field = SearchField::Genre;
        array<char, MAX_SIZE> search = { "Horror" };
        FindNodeResult result = library.findByField(search, field);
        printSearchedResult(result, search, field);
    }

    cout << endl;

    library.removeAfter(nullptr);
    library.removeAfter(library.head);

    library.printList();
    cout << "Size of list: " << library.size << endl;
    assertNoCycles(&library);

    return 0;
}
