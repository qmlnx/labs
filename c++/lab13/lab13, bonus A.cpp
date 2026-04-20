#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;

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
    cout << "   БОНУС А: ПЕРЕСЕЧЕНИЕ ДВУХ ПРЯМЫХ\n";
    
    // Тест 17: x + 4y = 3  и  2x + 5y = 7
    double a1 = 1, b1 = 4, c1 = 3;
    double a2 = 2, b2 = 5, c2 = 7;
    
    cout << "Прямая 1: " << a1 << "x + " << b1 << "y = " << c1 << endl;
    cout << "Прямая 2: " << a2 << "x + " << b2 << "y = " << c2 << endl << endl;
    
    // Решение системы
    vector<vector<double>> a(2, vector<double>(2));
    vector<double> bb(2);
    a[0][0] = a1; a[0][1] = b1; bb[0] = c1;
    a[1][0] = a2; a[1][1] = b2; bb[1] = c2;
    
    stepen(a, bb, 2, 2);
    
    double x = bb[0];
    double y = bb[1];
    
    cout << "РЕЗУЛЬТАТ: Точка пересечения:\n";
    cout << "  x = " << fixed << setprecision(4) << x << endl;
    cout << "  y = " << y << endl;
    
    // Создаём график
    ofstream gnu("graph.gnu");
    gnu << "set title 'Пересечение двух прямых (Тест 17)'\n";
    gnu << "set xlabel 'x'\nset ylabel 'y'\n";
    gnu << "set grid\n";
    gnu << "set xrange [-5:10]\n";
    gnu << "set yrange [-5:10]\n";
    gnu << "f1(x) = (" << c1 << " - " << a1 << "*x)/" << b1 << "\n";
    gnu << "f2(x) = (" << c2 << " - " << a2 << "*x)/" << b2 << "\n";
    gnu << "plot f1(x) title '" << a1 << "x + " << b1 << "y = " << c1 << "', \\\n";
    gnu << "     f2(x) title '" << a2 << "x + " << b2 << "y = " << c2 << "', \\\n";
    gnu << "     '-' with points pointtype 7 pointsize 2 title 'Точка (" << x << ", " << y << ")'\n";
    gnu << x << " " << y << "\n";
    gnu << "e\n";
    gnu.close();
    
    cout << "ГРАФИК СОЗДАН!\n";
    cout << "Для просмотра графика выполни:\n";
    cout << "  gnuplot -persist graph.gnu\n\n";
    
    cout << "Нажми Enter, чтобы выйти...";
    cin.ignore();
    cin.get();
    
    return 0;
}