#include <iostream>
#include <array>

using namespace std;

const int MAX_SIZE = 30;

enum class Genre {

	Classics,
	Novel,
	Detective,
	Fantasy,
	Horror,
	History

};

struct Book {

	array<char, MAX_SIZE> title;
	int pages;
	Genre genre;

};

void serializeTitle(const Book& book, ostream& os) {

	os << book.title.data();
}

void serializePages(const Book& book, ostream& os) {

	os << book.pages;
}

void serializeGenre(const Book& book, ostream& os) {

	os << static_cast<int>(book.genre);
}

void serializeBook(const Book& book, ostream& os) {

	serializeTitle(book, os);
	os << ", ";
	serializePages(book, os);
	os << ", ";
	serializeGenre(book, os);
	os << "\n";
}

int main() {

	return 0;
}