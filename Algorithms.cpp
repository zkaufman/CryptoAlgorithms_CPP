#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Algorithms {
public:
  static int GDC(int, int);
  static int FEA(int, int, int);
  static std::vector<int> Z(int);
  static std::vector<int> primitiveInts(int);
};

// Greatest common divisor.
// x = the bigger number
// y = the smaller number
int GCD(int x, int y) {

  while (y != 0) {
    int remainder = x % y;
    x = y;
    y = remainder;
  }

  return x;
}

// Calculates the group Z sub n
// Example:
//   n = 14
//   Z_n( n ) = { 1, 3, 5, 9, 11, 13 }
std::vector<int> Z_n(int n) {

  vector< int > Z;

  for ( int i=0 ; i < n ; i++ ) {
    int gcd = GCD(i,n);
    if (gcd == 1) {
      Z.push_back(i);
    }
  }

  return Z;
}

// Fast Exponentiation algorithm.
// Returns x^e mod m
// Example:
//   x = 8, e = 2, m = 13
//   (8)^2 % 13 = 12
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

// Calculates the primitive roots of a number n.
// Example:
//   n = 26
//   primitive rootes = { 7 11 15 19 }
std::vector<int> primitiveRoots(int n) {

  vector< int > primitive_roots;
  std::vector<int> Z = Z_n(n);
  int phi = Z.size();

  int z;
  int val;
  for ( int i = 0 ; i < phi ; i++ ) {
    vector<int> Z_temp = Z;
    z = Z[i];
    cout << z << "  |   ";
    for ( int ii = 1 ; ii <= phi ; ii++) {
      val = FEA(z, ii, n);
      Z_temp.erase(std::remove(Z_temp.begin(), Z_temp.end(), val), Z_temp.end());
      cout << val << "   ";
    }
    cout << endl;

    if (Z_temp.size() == 0)
      primitive_roots.push_back(z);
  }

  return primitive_roots;
}

int main(int argc, char *argv[]) {
  cout << "Running in C++" << endl;

  // Test GCD code.
  int x = 1024;
  int y = 888;
  int gcd = GCD(x, y);
  cout << "GCD for  " << x << " and " << y << " is: " << gcd << endl;

  // Test Fast Exponentiation Algorithm code.
  int base = 8;
  int e = 2;
  int m = 13;
  int val = FEA(base, e, m);
  cout << x << "^" << e << " % " << m << " = " << val << endl;

  // Test Z_n code.
  int n = 14;
  vector<int> Z = Z_n(n);
  cout << "Z_" << n << " = { ";
  for ( int i = 0 ; i < Z.size() ; i++ )
      cout << Z.at(i) << " ";
  cout << "}" << endl;


  // Test Primitive Roots algorithms.
  vector<int> primitive_roots = primitiveRoots(26);
  cout << "primitive_roots = { ";
  for ( int i = 0 ; i < primitive_roots.size() ; i++ )
      cout << primitive_roots.at(i) << " ";
  cout << "}" << endl;
}

