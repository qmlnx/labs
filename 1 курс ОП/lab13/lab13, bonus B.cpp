#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;

// Функция приведения к ступенчатому виду (метод Гаусса-Жордана)
void stepen(vector<vector<double>>& a, vector<double>& b, int n, int m) {
    for (int col = 0; col < m; col++) {
        int gl = col;
        for (int i = col; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[gl][col])) gl = i;
        }
        if (fabs(a[gl][col]) < EPS) continue;
        
        swap(a[col], a[gl]);
        swap(b[col], b[gl]);
        
        double d = a[col][col];
        for (int j = col; j < m; j++) a[col][j] /= d;
        b[col] /= d;
        
        for (int i = 0; i < n; i++) {
            if (i != col && fabs(a[i][col]) > EPS) {
                double k = a[i][col];
                for (int j = col; j < m; j++) a[i][j] -= k * a[col][j];
                b[i] -= k * b[col];
            }
        }
    }
}

int main() {
    cout << "========================================\n";
    cout << "   БОНУС Б: ПЕРЕСЕЧЕНИЕ ТРЁХ ПЛОСКОСТЕЙ\n";
    cout << "========================================\n\n";
    
    // ТЕСТ 20 (из задания)
    // Плоскости:
    // x + y + z = 1
    // x - 2y = 0
    // 2x + y + 3z = -1
    
    double a1 = 1, b1 = 1, c1 = 1, d1 = 1;
    double a2 = 1, b2 = -2, c2 = 0, d2 = 0;
    double a3 = 2, b3 = 1, c3 = 3, d3 = -1;
    
    cout << "ТЕСТ 20:\n";
    cout << "Плоскость 1: " << a1 << "x + " << b1 << "y + " << c1 << "z = " << d1 << endl;
    cout << "Плоскость 2: " << a2 << "x + " << b2 << "y + " << c2 << "z = " << d2 << endl;
    cout << "Плоскость 3: " << a3 << "x + " << b3 << "y + " << c3 << "z = " << d3 << endl;
    cout << "========================================\n\n";
    
    // Составляем матрицу 3x3
    vector<vector<double>> a(3, vector<double>(3));
    vector<double> b(3);
    
    a[0][0] = a1; a[0][1] = b1; a[0][2] = c1; b[0] = d1;
    a[1][0] = a2; a[1][1] = b2; a[1][2] = c2; b[1] = d2;
    a[2][0] = a3; a[2][1] = b3; a[2][2] = c3; b[2] = d3;
    
    // Решаем систему
    stepen(a, b, 3, 3);
    
    // Проверка на несовместность
    bool nesovmestna = false;
    for (int i = 0; i < 3; i++) {
        bool nul = true;
        for (int j = 0; j < 3; j++) {
            if (fabs(a[i][j]) > EPS) { nul = false; break; }
        }
        if (nul && fabs(b[i]) > EPS) nesovmestna = true;
    }
    
    if (nesovmestna) {
        cout << "РЕЗУЛЬТАТ: Плоскости не пересекаются в одной точке (нет решения)\n";
        return 0;
    }
    
    // Считаем ранг
    int rang = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (fabs(a[i][j]) > EPS) { rang++; break; }
        }
    }
    
    if (rang < 3) {
        cout << "РЕЗУЛЬТАТ: Плоскости пересекаются по прямой или совпадают (бесконечно много решений)\n";
        return 0;
    }
    
    // Выводим точку пересечения
    cout << "РЕЗУЛЬТАТ: Точка пересечения трёх плоскостей:\n";
    cout << "  x = " << fixed << setprecision(4) << b[0] << endl;
    cout << "  y = " << b[1] << endl;
    cout << "  z = " << b[2] << endl;
    
    cout << "\n========================================\n";
    cout << "Проверка:\n";
    cout << "  " << a1 << "*" << b[0] << " + " << b1 << "*" << b[1] << " + " << c1 << "*" << b[2] << " = " 
         << a1*b[0] + b1*b[1] + c1*b[2] << " (должно быть " << d1 << ")\n";
    cout << "  " << a2 << "*" << b[0] << " + " << b2 << "*" << b[1] << " + " << c2 << "*" << b[2] << " = " 
         << a2*b[0] + b2*b[1] + c2*b[2] << " (должно быть " << d2 << ")\n";
    cout << "  " << a3 << "*" << b[0] << " + " << b3 << "*" << b[1] << " + " << c3 << "*" << b[2] << " = " 
         << a3*b[0] + b3*b[1] + c3*b[2] << " (должно быть " << d3 << ")\n";
    cout << "========================================\n";
    
    return 0;
}