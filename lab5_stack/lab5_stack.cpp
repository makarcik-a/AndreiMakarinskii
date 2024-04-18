#include "../Books.h"

//Linked List
template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct Stack {
    Node<T>* top;
};

template<typename T>
bool isEmpty(const Stack<T>* stack) {
    return stack->top == nullptr;
}

template<typename T>
void push(Stack<T>* stack, T value) {
    Node<T>* newNode = new Node<T>{ value, stack->top };
    stack->top = newNode;
}

template<typename T>
T* getLastElement(Stack<T>* stack) {
    if (isEmpty(stack)) {
        std::cout << "Error: Stack is empty." << std::endl;
        return nullptr;
    }
    return &(stack->top->data);
}

template<typename T>
void pop(Stack<T>* stack) {
    if (isEmpty(stack)) {
        std::cout << "Error: Stack is empty." << std::endl;
        return;
    }
    Node<T>* temp = stack->top;
    stack->top = stack->top->next;
    delete temp;
}

//std::vector
void push(std::vector<Book>& stack, const Book& book) {
    stack.push_back(book);
}

bool isEmpty(const std::vector<Book>& stack) {
    return stack.empty();
}

Book* getLastElement(std::vector<Book>& stack) {
    if (isEmpty(stack)) {
        std::cout << "Error: Stack is empty." << std::endl;
        return nullptr;
    }
    return &stack.back();
}

void pop(std::vector<Book>& stack) {
    if (isEmpty(stack)) {
        std::cout << "Error: Stack is empty." << std::endl;
        return;
    }
    stack.pop_back();
}


int main() {

    Book book1{ "War and Peace", 1225, Genre::Classics };
    Book book2{ "1984", 328, Genre::Novel };
    Book book3{ "Sherlock Holmes", 448, Genre::Detective };
    
    { //Realization via linked list

        std::cout << "Implimenting stack via Linked List: " << std::endl;

        Stack<Book> bookStack{ nullptr };

        push(&bookStack, book1);
        push(&bookStack, book2);
        push(&bookStack, book3);

        if (!isEmpty(&bookStack)) {
            Book* topBook = getLastElement(&bookStack);
            if (topBook != nullptr) {
                std::cout << "Top book: " << topBook->title.data() << std::endl;
            }

            pop(&bookStack);

            topBook = getLastElement(&bookStack);
            if (topBook != nullptr) {
                std::cout << "Top book after pop: " << topBook->title.data() << std::endl;
            }
        }
        else {
            std::cout << "Stack is empty" << std::endl;
        }
    }

    std::cout << std::endl;

    { //Realization via std::vector

        std::cout << "Implimenting stack via std::vector: " << std::endl;

        std::vector<Book> bookStack;

        push(bookStack, book2);
        push(bookStack, book3);
        push(bookStack, book1);

        if (!isEmpty(bookStack)) {
            Book* topBook = getLastElement(bookStack);
            if (topBook != nullptr) {
                std::cout << "Top book: " << topBook->title.data() << std::endl;
            }

            pop(bookStack);

            topBook = getLastElement(bookStack);
            if (topBook != nullptr) {
                std::cout << "Top book after pop: " << topBook->title.data() << std::endl;
            }
        }
        else {
            std::cout << "Stack is empty" << std::endl;
        }
    }

	return 0;
}