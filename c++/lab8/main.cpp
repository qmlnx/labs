#include <iostream>
using namespace std;
//УПРАЖНЕНИЕ 2
void modifyValues(int& refArg, int* ptrArg)
{
    refArg = 100;
    *ptrArg = 200;
}

void exercise2()
{
    cout << "\nУПРАЖНЕНИЕ 2" << endl;
    
    int a = 5;
    int b = 7;
    
    cout << "До: a = " << a << ", b = " << b << endl;
    modifyValues(a, &b);
    cout << "После: a = " << a << ", b = " << b << endl;
}

// УПРАЖНЕНИЕ 4 
struct Node {
    int data;
    Node* prev;
    Node* next;
    
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    void append(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    void printBackward() {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

void exercise4()
{
    cout << "\nУПРАЖНЕНИЕ 4" << endl;
    
    DoublyLinkedList list;
    
    for (int i = 1; i <= 10; i++) {
        list.append(i);
    }
    
    cout << "Список (начало->конец): ";
    list.printForward();
    
    cout << "Список (конец->начало): ";
    list.printBackward();
}

int main()
{
    cout << "ЛАБОРАТОРНАЯ РАБОТА №8" << endl;

    exercise2();
    exercise4();
    
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//УПРАЖНЕНИЕ 3
//ЧАСТЬ 1: 4 варианта заполнения массива

// Вариант 1: статический массив, индексная адресация
void variant1() {
    cout << "\n--- ВАРИАНТ 1: Статический массив, индексы ---" << endl;
    const int SIZE = 10;
    int arr[SIZE];
    
    // Заполнение (индексная адресация)
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i * i;
    }
    
    // Вывод (индексная адресация)
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

// Вариант 2: статический массив, адресация через указатель
void variant2() {
    cout << "\n--- ВАРИАНТ 2: Статический массив, указатели ---" << endl;
    const int SIZE = 10;
    int arr[SIZE];
    int* ptr = arr;
    
    // Заполнение (косвенная адресация)
    for (int i = 0; i < SIZE; i++) {
        *(ptr + i) = i * i;
    }
    
    // Вывод (косвенная адресация)
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << *(ptr + i) << endl;
    }
}

// Вариант 3: динамический массив, индексная адресация
void variant3() {
    cout << "\n--- ВАРИАНТ 3: Динамический массив, индексы ---" << endl;
    const int SIZE = 10;
    int* arr = new int[SIZE];
    
    // Заполнение (индексная адресация)
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i * i;
    }
    
    // Вывод (индексная адресация)
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    
    delete[] arr;
}

// Вариант 4: динамический массив, адресация через указатель
void variant4() {
    cout << "\n--- ВАРИАНТ 4: Динамический массив, указатели ---" << endl;
    const int SIZE = 10;
    int* arr = new int[SIZE];
    int* ptr = arr;
    
    // Заполнение (косвенная адресация)
    for (int i = 0; i < SIZE; i++) {
        *(ptr + i) = i * i;
    }
    
    // Вывод (косвенная адресация)
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << *(ptr + i) << endl;
    }
    
    delete[] arr;
}