#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Algorithms {
public:
  static int MI(int, int);
  static int GDC(int, int);
  static int FEA(int, int, int);
  static std::vector<int> Z(int);
  static std::vector<int> primitiveInts(int);
};

// Multipilicative Inverse (brute force).
// Returns the mulitplicitive inverse of x
// such that: ax = by + 1. Returns a.
// Example:
//   MI(200, 313) is: 36
//   (36)(200) = (somenumber)(313) + 1
int MI(int base, int mod) {
  int remainder = 0;

  for(int b = 0; b < 16000 ; b++) {
    for (int a = 0; a < 16000; a++) {
      remainder = (base * a) - (mod * b);
      if (remainder == 1)
        return a;
    }
  }

  return -1;
}

// Greatest common divisor.
// x = the bigger number
// y = the smaller number
// Example:
//    GCD(899, 1914) is: 29
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
//   Z_n(14) is: { 1, 3, 5, 9, 11, 13 }
std::vector<int> Z_n(int n) {
  vector< int > Z;

  for ( int i=0 ; i < n ; i++ ) {
    int gcd = GCD(i,n);
    if (gcd == 1)
      Z.push_back(i);
  }

  return Z;
}

// Fast Exponentiation algorithm.
// Returns x^e mod m
// Example:
//   FEA(8, 2, 13) is: 12
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
//   primitiveRoots(26) is: { 7 11 15 19 }
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

// Baby-step Giant-step Algorithm.
// Calulates log_b(x) mod p.
// Example:
//    BSGS(2,3,101) is: 69
//    Log_2(3) mod 101 = 69
int BSGS(int logbase, int x, int mod) {
  int m = floor( sqrt(mod - 1) );
  vector<int> vec(m);

  // Calculate c.
  int mult_inv = MI(logbase, mod);
  int c = FEA(mult_inv, m, mod);
  cout << "c = " << c << endl;

  for ( int i = 0 ; i < m ; i++ ) {
    vec[i] = FEA(logbase,i,mod);
    cout << i << ", " << vec[i] << endl;
  }

  // vec should be sorted based on the second element
  // of the pair. Skippimng that step for now.
  // sort(vec)

  int temp_x = x;
  int j;
  int i = 0;
  vector<int>::iterator it;
  while (i < m) {
    it = std::find(vec.begin(), vec.end(), temp_x);

    cout << "temp_x = " << temp_x << ", it = " << (*it) << ", other = " << std::distance(vec.begin(), it) << endl;
    if (*it != 0) {
      j = it - vec.begin();
      break;
    }
    temp_x = (temp_x * c) % mod;
    i++;
  }

  cout << "log_" << logbase << "(" << x << ")" << " % " << mod << " = " <<
          m << " * " << i << " + " << j << " = ";
  if (j==0)
    return 0;
  else
    return (m*i + j);
}

int main(int argc, char *argv[]) {
  cout << "Running in C++" << endl;

  // Test Multiplicative Inverse.
  int base = 3;
  int mod = 12091;
  cout << "Muyltiplicative Inverse for " << base << " mod " << mod << " = " << MI(base, mod) << endl;

  // Test Greatest Common Denominator code.
  int x = 899;
  int y = 1914;
  int gcd = GCD(x, y);
  cout << "GCD for  " << x << " and " << y << " is: " << gcd << endl;

  // Test Fast Exponentiation Algorithm code.
  base = 11;
  int e = 9;
  int m = 29;
  int val = FEA(base, e, m);
  cout << base << "^" << e << " % " << m << " = " << val << endl;

  // Test Z_n code.
  int n = 26;
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

  // Test Baby-step Giant-step algorithm.
  int b = 2;
  x = 3;
  int p = 101;
  val = BSGS(b, x, p);
  cout << val << endl;

}

