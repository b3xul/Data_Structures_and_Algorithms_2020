#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int gcd(int a, int b);

int main(int argc, char **argv) {
  int a, b;

  printf("Input a e b: ");
  scanf("%d %d", &a, &b);

  printf("Massimo comun divisore di %d e %d: %d\n", a, b, gcd(a,b));
  return 0;
}

int gcd(int a, int b) {
  int tmp;
  if (a < b) {
    tmp = a;
    a = b;
    b = tmp;
  }
  if ((a == b) || (b == 0))
    return a;

  if (a%2 == 0 && b%2 == 0)
    return 2*gcd(a/2, b/2);
  else if (a%2 != 0 && b%2 == 0)
    return gcd(a, b/2);
  else if (a%2 == 0 && b%2 != 0)
    return gcd(a/2, b);
  else if (a%2 != 0 && b%2 != 0)
    return gcd((a-b)/2, b);
  else return 1;
}
