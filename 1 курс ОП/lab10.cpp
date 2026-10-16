#include <iostream>
#include <cstring>
using namespace std;

unsigned char* packData(const int arr[], int size, int& packedSize);
void unpackData(const unsigned char* packed, int originalSize, int result[]);

int main()
{
    cout << "УПРАЖНЕНИЕ 2 (Гармошка)" << endl;
    
    const int N = 1500; // длина массива (>1000)
    const int MAX_VALUE = 17; // максимальное значение элемента
    
    // Создаем упорядоченный целочисленный массив
    int arr[N];
    cout << "Создание упорядоченного массива из " << N << " элементов" << endl;
    cout << "Значения элементов в интервале [0, " << MAX_VALUE << "]" << endl;
    
    // Заполняем массив упорядоченными значениями от 0 до 17
    for(int i = 0; i < N; i++)
    {
        arr[i] = i % (MAX_VALUE + 1); // значения циклически повторяются: 0,1,2,...,17,0,1,...
    }
    
    // Выводим первые 30 элементов для проверки
    cout << "\nПервые 30 элементов исходного массива: " << endl;
    for(int i = 0; i < 30; i++)
    {
        cout << arr[i] << " ";
        if ((i + 1) % 15 == 0) cout << endl;
    }
    cout << endl;
    
    // А. Упаковка данных
    cout << "\n--- ЧАСТЬ А: Упаковка данных ---" << endl;
    int packedSize;
    unsigned char* packed = packData(arr, N, packedSize);
    
    cout << "Размер исходного массива: " << N * sizeof(int) << " байт" << endl;
    cout << "Размер упакованных данных: " << packedSize << " байт" << endl;
    
    double savings = 100.0 - (packedSize * 100.0 / (N * sizeof(int)));
    cout << "Экономия памяти: " << savings << "%" << endl;
    
    // Выводим первые несколько байт упакованных данных (в двоичном виде)
    cout << "\nПервые 10 байт упакованных данных (в двоичном виде):" << endl;
    for(int i = 0; i < 10 && i < packedSize; i++)
    {
        cout << "Байт " << i << ": ";
        for(int bit = 7; bit >= 0; bit--)
        {
            cout << ((packed[i] >> bit) & 1);
        }
        cout << endl;
    }
    cout << endl;
    
    // Б. Распаковка данных
    cout << "--- ЧАСТЬ Б: Распаковка данных ---" << endl;
    int* unpacked = new int[N];
    unpackData(packed, N, unpacked);
    
    // Выводим первые 30 элементов распакованного массива
    cout << "Первые 30 элементов распакованного массива: " << endl;
    for(int i = 0; i < 30; i++)
    {
        cout << unpacked[i] << " ";
        if ((i + 1) % 15 == 0) cout << endl;
    }
    cout << endl;
    
    // Проверка корректности распаковки
    bool correct = true;
    for(int i = 0; i < N; i++)
    {
        if(arr[i] != unpacked[i])
        {
            correct = false;
            cout << "Ошибка в позиции " << i << ": "
                 << "ожидалось " << arr[i] 
                 << ", получено " << unpacked[i] << endl;
            break;
        }
    }
    
    cout << "\nРезультат: ";
    if(correct)
    {
        cout << "Данные успешно упакованы и распакованы!" << endl;
        cout << "Исходный массив полностью восстановлен." << endl;
    }
    else
    {
        cout << "Ошибка при распаковке данных!" << endl;
    }
    
    // Очистка памяти
    delete[] packed;
    delete[] unpacked;
    
    return 0;
}

// А. Функция упаковки данных
unsigned char* packData(const int arr[], int size, int& packedSize)
{
    // Каждое число от 0 до 17 занимает 5 бит (2^5 = 32, что больше 17)
    int totalBits = size * 5;
    
    // Вычисляем количество байт (с округлением вверх)
    packedSize = (totalBits + 7) / 8;
    
    // Выделяем память под упакованные данные
    unsigned char* packed = new unsigned char[packedSize];
    
    // Обнуляем память
    for(int i = 0; i < packedSize; i++)
    {
        packed[i] = 0;
    }
    
    int bitPos = 0; // текущая позиция в битах
    
    // Упаковываем каждое значение
    for(int i = 0; i < size; i++)
    {
        int value = arr[i];
        
        // Записываем 5 бит значения
        for(int bit = 0; bit < 5; bit++)
        {
            // Определяем, в каком байте и бите находится текущая позиция
            int byteIndex = bitPos / 8;
            int bitIndex = bitPos % 8;
            
            // Проверяем bit-й бит значения
            if(value & (1 << bit))
            {
                // Устанавливаем соответствующий бит в упакованных данных
                packed[byteIndex] |= (1 << bitIndex);
            }
            
            bitPos++; 
        }
    }
    
    return packed;
}

// Б. Функция распаковки данных
void unpackData(const unsigned char* packed, int originalSize, int result[])
{
    int bitPos = 0; // текущая позиция в битах
    
    // Распаковываем каждое значение
    for(int i = 0; i < originalSize; i++)
    {
        int value = 0;
        
        // Читаем 5 бит для каждого значения
        for(int bit = 0; bit < 5; bit++)
        {
            // Определяем, из какого байта и бита читаем
            int byteIndex = bitPos / 8;
            int bitIndex = bitPos % 8;
            
            // Проверяем бит в упакованных данных
            if(packed[byteIndex] & (1 << bitIndex))
            {
                // Устанавливаем соответствующий бит в значении
                value |= (1 << bit);
            }
            
            bitPos++;
        }
        
        result[i] = value;
    }
}