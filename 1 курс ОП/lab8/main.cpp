#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// УПРАЖНЕНИЕ 2
void modifyValues(int& refArg, int* ptrArg)
{
    refArg = 100; //сслыка
    *ptrArg = 200; //указатель
}

void exercise2()
{
    cout << "\n УПРАЖНЕНИЕ 2" << endl;
    
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
    
    void append(int value) { //выделяем память
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
    cout << "\n УПРАЖНЕНИЕ 4 " << endl;
    
    DoublyLinkedList list;
    
    for (int i = 1; i <= 10; i++) {
        list.append(i);
    }
    
    cout << "Список (начало->конец): ";
    list.printForward();
    
    cout << "Список (конец->начало): ";
    list.printBackward();
}

// УПРАЖНЕНИЕ 3 
// Часть 1: 4 варианта заполнения массива

// Вариант 1: статический массив, индексная адресация
void variant1() {
    cout << "\n ВАРИАНТ 1: Статический массив, индексы" << endl;
    const int SIZE = 10;
    int arr[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i * i;
    }
    
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

// Вариант 2: статический массив, адресация через указатель
void variant2() {
    cout << "\n ВАРИАНТ 2: Статический массив, указатели" << endl;
    const int SIZE = 10;
    int arr[SIZE];
    int* ptr = arr;
    
    for (int i = 0; i < SIZE; i++) {
        *(ptr + i) = i * i;  //сдвиг  на i вперед
    }
    
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << *(ptr + i) << endl;
    }
}

// Вариант 3: динамический массив, индексная адресация
void variant3() {
    cout << "\n ВАРИАНТ 3: Динамический массив, индексы " << endl;
    const int SIZE = 10;
    int* arr = new int[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i * i;
    }
    
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    
    delete[] arr;
}

// Вариант 4: динамический массив, адресация через указатель
void variant4() {
    cout << "\n ВАРИАНТ 4: Динамический массив, указатели " << endl;
    const int SIZE = 10;
    int* arr = new int[SIZE];
    int* ptr = arr;
    
    for (int i = 0; i < SIZE; i++) {
        *(ptr + i) = i * i;
    }
    
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = " << *(ptr + i) << endl;
    }
    
    delete[] arr;
}

// Часть 2: Объединение двух упорядоченных массивов

void fillAndSortArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArrayIndex(int* arr, int size, const char* name) {
    cout << name << " (индексы): ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printArrayPointer(int* arr, int size, const char* name) {
    cout << name << " (указатели): ";
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int* mergeArrays(int* arr1, int size1, int* arr2, int size2, int& resultSize) {
    resultSize = size1 + size2;
    int* result = new int[resultSize];
    int* ptr = result;
    
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            *(ptr + k) = arr1[i];
            i++;
        } else {
            *(ptr + k) = arr2[j];
            j++;
        }
        k++;
    }
    
    while (i < size1) {
        *(ptr + k) = arr1[i];
        i++;
        k++;
    }
    
    while (j < size2) {
        *(ptr + k) = arr2[j];
        j++;
        k++;
    }
    
    return result;
}

void demonstrateMerge() {
    cout << "\n ЧАСТЬ 2: ОБЪЕДИНЕНИЕ МАССИВОВ " << endl;
    
    srand(time(0));
    
    int size1 = 7;
    int size2 = 10;
    
    int* arr1 = new int[size1];
    int* arr2 = new int[size2];
    
    fillAndSortArray(arr1, size1);
    fillAndSortArray(arr2, size2);
    
    cout << "\nИсходные упорядоченные массивы:" << endl;
    printArrayIndex(arr1, size1, "Массив 1");
    printArrayPointer(arr2, size2, "Массив 2");
    
    int resultSize;
    int* result = mergeArrays(arr1, size1, arr2, size2, resultSize);
    
    cout << "\nРезультирующий упорядоченный массив:" << endl;
    printArrayPointer(result, resultSize, "Результат");
    
    delete[] arr1;
    delete[] arr2;
    delete[] result;
}

void exercise3() {
    cout << "\n УПРАЖНЕНИЕ 3" << endl;
    
    cout << "\n Часть 1: 4 варианта заполнения массива " << endl;
    variant1();
    variant2();
    variant3();
    variant4();
    
    demonstrateMerge();
}

// ГЛАВНАЯ ФУНКЦИЯ 
int main() {
    cout << "     ЛАБОРАТОРНАЯ РАБОТА №8" << endl;
    
    exercise2();
    exercise3();
    exercise4();
    
    cout << "           РАБОТА ЗАВЕРШЕНА" << endl;
    
    return 0;
}