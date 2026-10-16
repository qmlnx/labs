#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;

void stepen(vector<vector<double>>& a, vector<double>& b, int n, int m) {
    // поиск главного элемента
    for (int col = 0; col < m; col++) { //ищем самый большой эл в столбце
        int gl = col;
        for (int i = col; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[gl][col])) gl = i;
        }
        if (fabs(a[gl][col]) < EPS) continue; // столбец нулевой - пропускаем
        
        swap(a[col], a[gl]); // меняем строки местами
        swap(b[col], b[gl]);
        
        double d = a[col][col]; // делим строку на ведущий элемент, чтобы получить 1
        for (int j = col; j < m; j++) a[col][j] /= d;
        b[col] /= d;
        
        for (int i = 0; i < n; i++) { // обнуляем другие строки в этом столбце
            if (i != col && fabs(a[i][col]) > EPS) {
                double k = a[i][col];
                for (int j = col; j < m; j++) a[i][j] -= k * a[col][j];
                b[i] -= k * b[col];
            }
        }
    }
}

int main() {
    string inputFile = "test9.txt"; // менять файл тут
    
    ifstream fin(inputFile); //чтение файла
    if (!fin) {
        cout << "Нет файла " << inputFile << endl;
        return 1;
    }
    
    int n, m;
    fin >> n >> m;
    
    vector<vector<double>> a(n, vector<double>(m)); //создание матрицы
    vector<double> b(n); //вектор свободных членов
    
    for (int i = 0; i < n; i++) { // заполнение из файла
        for (int j = 0; j < m; j++) fin >> a[i][j];
        fin >> b[i];
    }
    fin.close();
    
    stepen(a, b, n, m); // ступенчатый вид
    
    ofstream fout("output.txt");
    
    // Проверка на несовместность
    bool nesovmestna = false;
    for (int i = 0; i < n; i++) { //проходим по строкам
        bool nul = true; //предполагаем что все коэфф равны 0 в строке
        for (int j = 0; j < m; j++) { // проверяем есть ли ненулевые коэфф
            if (fabs(a[i][j]) > EPS) { nul = false; break; } 
        }
        if (nul && fabs(b[i]) > EPS) nesovmestna = true; //если строка 0, но свободный член не 0
    }
    
    if (nesovmestna) {
        cout << "\nСИСТЕМА НЕСОВМЕСТНА (РЕШЕНИЙ НЕТ)\n";
        fout << "СИСТЕМА НЕСОВМЕСТНА (РЕШЕНИЙ НЕТ)\n";
        return 0;
    }
    
    // Считаем ранг (кол-во ненудевых строк)
    int rang = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fabs(a[i][j]) > EPS) { rang++; break; }
        }
    }
    
    // Если единственное решение - сообщаем
    if (rang == m) {
        cout << "\nСИСТЕМА ИМЕЕТ ЕДИНСТВЕННОЕ РЕШЕНИЕ (см. задания 1-2)\n";
        fout << "СИСТЕМА ИМЕЕТ ЕДИНСТВЕННОЕ РЕШЕНИЕ (см. задания 1-2)\n";
        return 0;
    }
    
    // ========== ЗАДАНИЕ 3: ОБЩЕЕ РЕШЕНИЕ ==========
    cout << "\n=== ЗАДАНИЕ 3: ОБЩЕЕ РЕШЕНИЕ ===\n";
    fout << "\n=== ЗАДАНИЕ 3: ОБЩЕЕ РЕШЕНИЕ ===\n";
    
    // Находим базисные переменные ( у которых в матрице 1)
    vector<bool> bazis(m, false);
    vector<int> stroka(m, -1);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fabs(a[i][j] - 1.0) < EPS) { //нашли 1 в матрице
                bazis[j] = true; //эта переменная базисная
                stroka[j] = i; // запомнили строку
                break;
            }
        }
    }
    
    // Свободные переменные
    cout << "\nСвободные переменные: "; // выводим их все
    fout << "\nСвободные переменные: ";
    for (int j = 0; j < m; j++) {
        if (!bazis[j]) {
            cout << "x" << j+1 << " ";
            fout << "x" << j+1 << " ";
        }
    }
    cout << "\n";
    fout << "\n";
    
    // Частное решение (вычисляет одно кокнретное решение, где все свободные переменные равны 0)
    cout << "\nЧастное решение (свободные = 0):\n";
    fout << "\nЧастное решение (свободные = 0):\n";
    for (int j = 0; j < m; j++) { //перепоб переменных
        if (bazis[j]) { //если переменная базисная
            cout << "x" << j+1 << " = " << fixed << setprecision(4) << b[stroka[j]] << endl;
            fout << "x" << j+1 << " = " << fixed << setprecision(4) << b[stroka[j]] << endl;
        } else { //если переменная свободная
            cout << "x" << j+1 << " = 0 (свободная)\n";
            fout << "x" << j+1 << " = 0 (свободная)\n";
        }
    }
    
    // Общее решение
    cout << "\nОбщее решение:\n";
    fout << "\nОбщее решение:\n";
    for (int j = 0; j < m; j++) { //перебор переменных
        if (bazis[j]) { //проверяем базисная ли
            int str = stroka[j];
            cout << "x" << j+1 << " = " << fixed << setprecision(4) << b[str];
            fout << "x" << j+1 << " = " << fixed << setprecision(4) << b[str];
            for (int k = 0; k < m; k++) { //ищем коэффициенты при свободных переменных
                if (!bazis[k] && fabs(a[str][k]) > EPS) {
                    double koef = -a[str][k]; //вычисляем коэффициент
                    if (koef > 0) {
                        cout << " + " << koef << "*x" << k+1;
                        fout << " + " << koef << "*x" << k+1;
                    } else {
                        cout << " - " << fabs(koef) << "*x" << k+1;
                        fout << " - " << fabs(koef) << "*x" << k+1;
                    }
                }
            }
            cout << endl;
            fout << endl;
        }
    }
    
    fout.close();
    cout << "\nРезультат в output.txt\n";
    
    return 0;
}