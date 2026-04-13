#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;

void stepen(vector<vector<double>>& a, vector<double>& b, int n, int m) { //функция ступенчатого вида
    // Проходим по всем столбцам слева направо
    for (int col = 0; col < m; col++) {
        //Ищем главный элемент (самый большой по модулю в столбце)
        int gl = col;
        for (int i = col; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[gl][col])) gl = i;
        }
        // Если весь столбец почти нулевой - пропускаем
        if (fabs(a[gl][col]) < EPS) continue;
        
        //меняем строки местами
        swap(a[col], a[gl]); 
        swap(b[col], b[gl]);
        
        //Делим строку на ведущий элемент (чтобы получить 1 на диагонали)
        double d = a[col][col];
        for (int j = col; j < m; j++) a[col][j] /= d;
        b[col] /= d;
        
        //Обнуляем все остальные строки в этом столбце
        for (int i = 0; i < n; i++) {
            if (i != col && fabs(a[i][col]) > EPS) {
                double k = a[i][col];
                for (int j = col; j < m; j++) a[i][j] -= k * a[col][j];
                b[i] -= k * b[col];
            }
        }
    }// В итоге: матрица a стала единичной, вектор b содержит решение
} 

int main() {
    string inputFile = "test9.txt"; //входной файл (1,9,13)
    
    ifstream fin(inputFile); //открываем файл
    if (!fin) {
        cout << "Нет файла " << inputFile << endl;
        return 1;
    }
    
    // Читаем размеры: n - число уравнений, m - число неизвестных
    int n, m;
    fin >> n >> m;
    
    // Создаём матрицу A (n x m) и вектор B (n)
    vector<vector<double>> a(n, vector<double>(m));
    vector<double> b(n);
    
    // Заполняем матрицу и вектор из файла
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) fin >> a[i][j];
        fin >> b[i];
    }
    fin.close(); //закрываем файл
    
    stepen(a, b, n, m); //приводим к ступенчатому виду
    
    // Вывод
    ofstream fout("output.txt");
    
    auto print = [&](ostream& out) { //функция для вывода
        // ЗАДАНИЕ 1: вывод ступенчатого вида
        out << "СТУПЕНЧАТЫЙ ВИД:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                out << fixed << setprecision(4) << a[i][j] << "\t";
            }
            out << "| " << fixed << setprecision(4) << b[i] << "\n";
        }
        
        //проверка есть ли вообще решение 
        // Ищем строку вида: 0 0 ... 0 | (не ноль)  →  решений нет
        bool net = false;
        for (int i = 0; i < n; i++) {
            bool nol = true; // предположим, строка нулевая
            for (int j = 0; j < m; j++) {
                if (fabs(a[i][j]) > EPS) nol = false; // нашли ненулевой элемент
            }
            if (nol && fabs(b[i]) > EPS) net = true; // строка нулевая, а b не ноль
        }
        
        if (net) {
            out << "\nРЕШЕНИЯ НЕТ\n";
        } else {
            int rang = 0; //считаем ранг матрицы, ранг = количество ненулевых строк
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (fabs(a[i][j]) > EPS) { rang++; break; }
                }
            }
            
            // ЗАДАНИЕ 2: единственное решение
            // Если ранг = числу неизвестных → решение единственное
            if (rang == m) {
                out << "\nЕДИНСТВЕННОЕ РЕШЕНИЕ:\n";
                // Из единичной матрицы забираем значения корней
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        if (fabs(a[i][j] - 1.0) < EPS) {
                            out << "x" << j+1 << " = " << fixed << setprecision(4) << b[i] << "\n";
                        }
                    }
                }
            } else {
                out << "\nНЕТ ЕДИНСТВЕННОГО РЕШЕНИЯ\n";
            }
        }
    };
    
    print(cout);   // вывод в терминал
    print(fout);   // вывод в файл
    
    fout.close();
    return 0;
}