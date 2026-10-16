// ЗАДАНИЕ 1 

#include <iostream>
#include <cstring>  // для C-строк
#include <string>   // для C++ строк
#include <clocale>  // для setlocale
using namespace std;

// Функция для обрезания UTF-8 строки до указанного количества символов
string truncateUTF8(const string& str, int max_chars) {
    if (max_chars <= 0) return "";
    
    int char_count = 0;
    int byte_index = 0;
    
    while (byte_index < str.length() && char_count < max_chars) {
        // Определяем, сколько байт в текущем символе UTF-8
        unsigned char c = str[byte_index];
        int bytes_in_char;
        
        if (c < 0x80) bytes_in_char = 1;        
        else if (c < 0xE0) bytes_in_char = 2;    
        else if (c < 0xF0) bytes_in_char = 3;    
        else bytes_in_char = 4;                  
        
        byte_index += bytes_in_char;
        char_count++;
    }
    
    return str.substr(0, byte_index);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // ЗАДАНИЕ 1: Демонстрация работы со строками

    cout << "            УПРАЖНЕНИЕ 1" << endl;
    
    // ЧАСТЬ 1: РАБОТА С C-СТРОКАМИ (char[])
    cout << "--- ЧАСТЬ 1: РАБОТА С C-СТРОКАМИ (char[]) ---\n" << endl;
    
    // 1. strlen() - определение длины строки
    char str1[] = "Привет";
    cout << "1. strlen() - длина строки:" << endl;
    cout << "   Строка: \"" << str1 << "\"" << endl;
    cout << "   Длина: " << strlen(str1) << endl << endl;
    
    // 2. strcpy() - копирование строк
    char str2[20];
    strcpy(str2, "Мир");
    cout << "2. strcpy() - копирование строки:" << endl;
    cout << "   Исходная строка: \"Мир\"" << endl;
    cout << "   Скопировано в str2: \"" << str2 << "\"" << endl << endl;
    
    // 3. strcat() - объединение строк
    char str3[30] = "Привет, ";
    strcat(str3, str2);
    cout << "3. strcat() - объединение строк:" << endl;
    cout << "   Результат объединения: \"" << str3 << "\"" << endl << endl;
    
    // ЧАСТЬ 2: РАБОТА С C++ СТРОКАМИ (string)
    cout << "--- ЧАСТЬ 2: РАБОТА С C++ СТРОКАМИ (string) ---\n" << endl;
    
    // 1. length() - длина строки
    string s1 = "Привет";
    cout << "1. length() - длина строки:" << endl;
    cout << "   Строка: \"" << s1 << "\"" << endl;
    cout << "   Длина: " << s1.length() << endl << endl;
    
    // 2. operator+ - объединение
    string s2 = "Мир";
    string s3_cpp = s1 + ", " + s2 + "!";
    cout << "2. operator+ - объединение строк:" << endl;
    cout << "   s1 = \"" << s1 << "\"" << endl;
    cout << "   s2 = \"" << s2 << "\"" << endl;
    cout << "   Результат s1 + s2 = \"" << s3_cpp << "\"" << endl << endl;
    
    // 3. substr() - извлечение подстроки
    cout << "3. substr() - извлечение подстроки:" << endl;
    cout << "   Исходная строка: \"" << s3_cpp << "\"" << endl;
    cout << "   Первые 3 символа: \"" << s3_cpp.substr(0, 3) << "\"" << endl;
    cout << "   Символы с 4-го по 6-й: \"" << s3_cpp.substr(3, 3) << "\"" << endl << endl;
    
    // ЗАДАНИЕ 4: Массив строк с четными номерами

    cout << "            УПРАЖНЕНИЕ 4" << endl;
    
    int n;
    cout << "Введите количество слов (не более 20): ";
    cin >> n;
    
    if (n > 20) {
        cout << "Слишком много слов. Будет использовано 20." << endl;
        n = 20;
    }
    
    // ВВОД ДАННЫХ
    string temp[20];
    
    cout << "Введите " << n << " слов(а):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Слово " << i + 1 << ": ";
        cin >> temp[i];
    }
    
    // ВАРИАНТ 1: C-строки (char) 

    cout << "\n--- ВАРИАНТ 1: C-строки (char) ---" << endl;
    cout << "Слова с четными номерами:" << endl;
    
    // Создаем массив C-строк
    char** c_words = new char* [n];
    for (int i = 0; i < n; i++) {
        // Обрезаем до 10 символов с учетом UTF-8
        string truncated = truncateUTF8(temp[i], 10);
        
        // Выделяем память под обрезанную строку
        c_words[i] = new char[truncated.length() + 1];
        strcpy(c_words[i], truncated.c_str());
    }
    
    // Вывод слов с четными номерами
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            cout << "  Индекс [" << i << "] - Порядковый №" << i + 1 
                 << ": " << c_words[i] << endl;
        }
    }
    
    // ВАРИАНТ 2: C++ строки (string) 

    cout << "\n--- ВАРИАНТ 2: C++ строки (string) ---" << endl;
    cout << "Слова с четными номерами:" << endl;
    
    // Вывод слов с четными номерами
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            cout << "  Индекс [" << i << "] - Порядковый №" << i + 1 
                 << ": " << temp[i] << endl;
        }
    }
    
    // ОСВОБОЖДЕНИЕ ПАМЯТИ
    
    for (int i = 0; i < n; i++) {
        delete[] c_words[i];
    }
    delete[] c_words;
    
    cout << "\nПрограмма завершена." << endl;
    return 0;
}