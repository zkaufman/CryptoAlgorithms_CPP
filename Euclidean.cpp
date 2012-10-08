#include <iostream>
#include <math.h>
using namespace std;

class Euclidean {
public:
  static int GDC(int, int);
};

int GCD(int x, int y) {

    while (y != 0) {
      int remainder = x % y;
      int divisor = floor ((float)x / y);
      cout << x << " - " << divisor << " x " << y << " = " << remainder;
      cout << endl;
      x = y;
      y = remainder;
    }

    return x;
}

int main(int argc, char *argv[]) {
  int x = atoi( argv[1]);
  int y = atoi( argv[2]);
  int gcd = GCD(x, y);
  cout << "GCD for  " << x << " and " << y << " is: " << gcd;

}

