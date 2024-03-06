#include <iostream>
#include <array>

using namespace std;

enum class Genre { 
	
	Classics, 
	Novel, 
	Detective,
	Fantasy, 
	Horror, 
	History 

};

struct Book {

	array<char, 30> title;
	int pages;
	Genre genre;

};


int main() {



	return 0;
}