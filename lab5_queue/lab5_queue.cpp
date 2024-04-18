#include "../Books.h"

template<typename T, int Size>
struct Queue {
    std::array<T, Size> elements;
    int head;
    int tail;
    int size;

    Queue() : elements{}, head(0), tail(-1), size(0) {}

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == Size;
    }

    void enqueue(const T& value) {
        if (isFull()) {
            std::cerr << "Queue is full." << std::endl;
            return;
        }
        tail = (tail + 1) % Size;
        elements[tail] = value;
        size++;
    }

    T* frontElement() {
        if (isEmpty()) {
            std::cout << "Queue is empty." << std::endl;
            return nullptr;
        }
        return &(elements[head]);
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty." << std::endl;
            return;
        }
        head = (head + 1) % Size;
        size--;
    }
};

int main() {
    
    Queue<Book, 5> queue;

    Book book1 { "The Hobbit", 300, Genre::Fantasy };
    Book book2 { "The Adventures of Sherlock Holmes", 307, Genre::Detective };
    Book book3 { "Harry Potter and the Philosopher's Stone", 320, Genre::Fantasy };

    queue.enqueue(book1);
    queue.enqueue(book2);
    queue.enqueue(book3);

    if (!queue.isEmpty()) {
        std::cout << "First element is: " << queue.frontElement()->title.data() << std::endl;

        queue.dequeue();

        std::cout << "First element after dequeue is: " << queue.frontElement()->title.data() << std::endl;
    }
    else {
        std::cout << "Queue is empty." << std::endl;
    }

    return 0;
}