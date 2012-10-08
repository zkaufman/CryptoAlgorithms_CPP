#include <iostream>
#include <math.h>
using namespace std;

class Euclidean {
public:
  static int GDC(int, int);
  static int FEA(int, int, int);
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

int FEA(int x, int e, int m) {

	int Y = 1;
	while (e != 0) {
		if (e % 2 == 0) {
		  x = ( (x * x) % m);
		  e = e / 2;
		} else {
		  e = e - 1;
		  Y = ( (x * Y) % m);
		}
	}

	return Y;
}

int main(int argc, char *argv[]) {
  cout << "Running in C++" << endl;
  if (argc == 3) {
    int x = atoi( argv[1] );
    int y = atoi( argv[2] );
    int gcd = GCD(x, y);
    cout << "GCD for  " << x << " and " << y << " is: " << gcd;
  } else if (argc == 4) {
    int x = atoi( argv[1] );
    int e = atoi( argv[2] );
    int m = atoi( argv[3] );
    int val = FEA(x, e, m);
    cout << x << "^" << e << " % " << m << " = " << val;
  }
}

