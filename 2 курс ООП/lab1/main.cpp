#include "figure.h"
#include "user.h"
#include <iostream>
using namespace std;

int main() {
    Rectangle r1(0,0,2, 2);
    Rectangle r2(3,3,5,5);

    User* u = new User (0,0,5,5);
    delete u;
    
    return 0;
}
