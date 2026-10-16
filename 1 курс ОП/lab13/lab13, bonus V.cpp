#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;

bool reshitSistemu(double a1, double b1, double c1,
                   double a2, double b2, double c2,
                   double& x, double& y) {
    double det = a1 * b2 - a2 * b1;
    if (fabs(det) < EPS) return false;
    
    x = (c1 * b2 - c2 * b1) / det;
    y = (a1 * c2 - a2 * c1) / det;
    return true;
}

int main() {
    cout << "========================================\n";
    cout << "   БОНУС В: ПЛОЩАДЬ ТРЕУГОЛЬНИКА\n";
    cout << "========================================\n\n";
    
    // ТЕСТ 29 (правильные коэффициенты)
    // Прямые:
    // -7x + 4y = -2
    // 5x + 2y = -18
    // 2x - 6y = -14
    
    double a1 = -7, b1 = 4, c1 = -2;
    double a2 = 5, b2 = 2, c2 = -18;
    double a3 = 2, b3 = -6, c3 = -14;   // ИСПРАВЛЕНО: было 3, стало 2
    
    cout << "ТЕСТ 29:\n";
    cout << "Прямая 1: " << a1 << "x + " << b1 << "y = " << c1 << endl;
    cout << "Прямая 2: " << a2 << "x + " << b2 << "y = " << c2 << endl;
    cout << "Прямая 3: " << a3 << "x + " << b3 << "y = " << c3 << endl;
    cout << "========================================\n\n";
    
    double x12, y12, x13, y13, x23, y23;
    
    if (!reshitSistemu(a1, b1, c1, a2, b2, c2, x12, y12)) {
        cout << "ОШИБКА: Прямые 1 и 2 параллельны\n";
        return 1;
    }
    if (!reshitSistemu(a1, b1, c1, a3, b3, c3, x13, y13)) {
        cout << "ОШИБКА: Прямые 1 и 3 параллельны\n";
        return 1;
    }
    if (!reshitSistemu(a2, b2, c2, a3, b3, c3, x23, y23)) {
        cout << "ОШИБКА: Прямые 2 и 3 параллельны\n";
        return 1;
    }
    
    double S = fabs((x12 - x13) * (y23 - y13) - (x23 - x13) * (y12 - y13)) / 2.0;
    
    cout << "Вершины треугольника:\n";
    cout << "  A (пересечение 1 и 2): (" << fixed << setprecision(4) << x12 << "; " << y12 << ")\n";
    cout << "  B (пересечение 1 и 3): (" << x13 << "; " << y13 << ")\n";
    cout << "  C (пересечение 2 и 3): (" << x23 << "; " << y23 << ")\n";
    cout << "\nПЛОЩАДЬ ТРЕУГОЛЬНИКА: " << S << endl;
    
    // Создаём файл для графика
    ofstream gnu("triangle.gnu");
    gnu << "set title 'Треугольник из трёх прямых (Тест 29)'\n";
    gnu << "set xlabel 'x'\nset ylabel 'y'\n";
    gnu << "set grid\n";
    gnu << "set xrange [-10:10]\n";
    gnu << "set yrange [-10:10]\n";
    gnu << "f1(x) = (" << c1 << " - " << a1 << "*x)/" << b1 << "\n";
    gnu << "f2(x) = (" << c2 << " - " << a2 << "*x)/" << b2 << "\n";
    gnu << "f3(x) = (" << c3 << " - " << a3 << "*x)/" << b3 << "\n";
    gnu << "plot f1(x) title '" << a1 << "x + " << b1 << "y = " << c1 << "', \\\n";
    gnu << "     f2(x) title '" << a2 << "x + " << b2 << "y = " << c2 << "', \\\n";
    gnu << "     f3(x) title '" << a3 << "x + " << b3 << "y = " << c3 << "', \\\n";
    gnu << "     '-' with linespoints linewidth 2 title 'Треугольник'\n";
    gnu << x12 << " " << y12 << "\n";
    gnu << x13 << " " << y13 << "\n";
    gnu << x23 << " " << y23 << "\n";
    gnu << x12 << " " << y12 << "\n";
    gnu << "e\n";
    gnu.close();
    
    cout << "\n========================================\n";
    cout << "График сохранён в triangle.gnu\n";
    cout << "Для просмотра выполни: gnuplot -persist triangle.gnu\n";
    cout << "========================================\n";
    
    return 0;
}