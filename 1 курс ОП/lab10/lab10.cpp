#include <iostream>
using namespace std;

// Прототипы
unsigned char* packData(const int arr[], int size, int& packedSize);
void unpackData(const unsigned char* packed, int originalSize, int result[]);

int main()
{
    const int N = 1500; // размер массива
    
    // Создаем массив
    int arr[N];
    for(int i = 0; i < N; i++)
        arr[i] = i % 18; // значения 0-17 по циклу
    
    // Выводим первые 30 элементов
    cout << "Исходный массив (первые 30): ";
    for(int i = 0; i < 30; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    // Упаковка
    int packedSize;
    unsigned char* packed = packData(arr, N, packedSize);
    
    cout << "Размер исходный: " << N * 4 << " байт" << endl;
    cout << "Размер упакованный: " << packedSize << " байт" << endl;
    cout << "Экономия: " << 100 - (packedSize * 100.0 / (N * 4)) << "%" << endl;
    
    // Распаковка
    int* unpacked = new int[N];
    unpackData(packed, N, unpacked);
    
    // Проверка(сравнение исходного массива с распакованным)
    bool ok = true;
    for(int i = 0; i < N; i++)
        if(arr[i] != unpacked[i]) ok = false;
    
    cout << "Результат: " << (ok ? "Успешно" : "Ошибка") << endl;
    
    // Очистка
    delete[] packed;
    delete[] unpacked;
    
    return 0;
}

// Функция упаковки
unsigned char* packData(const int arr[], int size, int& packedSize)
{
    packedSize = (size * 5 + 7) / 8; // сколько байт нужно(+7 для округл)
    unsigned char* packed = new unsigned char[packedSize];
    
    // Обнуляем (создание массива и заполнение нулями)
    for(int i = 0; i < packedSize; i++)
        packed[i] = 0;
    
    int bitPos = 0;
    for(int i = 0; i < size; i++)
    {
        int value = arr[i];
        for(int bit = 0; bit < 5; bit++)
        {
            int byteIndex = bitPos / 8;
            int bitIndex = bitPos % 8;
            
            if(value & (1 << bit))
                packed[byteIndex] |= (1 << bitIndex);
            
            bitPos++;
        }
    }
    return packed;
}

// Функция распаковки
void unpackData(const unsigned char* packed, int size, int result[])
{
    int bitPos = 0;
    for(int i = 0; i < size; i++)
    {
        int value = 0;
        for(int bit = 0; bit < 5; bit++)
        {
            int byteIndex = bitPos / 8;
            int bitIndex = bitPos % 8;
            
            if(packed[byteIndex] & (1 << bitIndex))
                value |= (1 << bit);
            
            bitPos++;
        }
        result[i] = value;
    }
}