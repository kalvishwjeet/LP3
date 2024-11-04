#include <iostream>
using namespace std;

// Iterative function to calculate the nth Fibonacci number
int fibonacciIterative(int n) {
    if (n <= 1) return n;

    int prev1 = 0, prev2 = 1, result = 0;
    
    for (int i = 2; i <= n; i++) {
        result = prev1 + prev2;
        prev1 = prev2;
        prev2 = result;
    }

    return result;
}

int fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Iterative Fibonacci of " << n << " is " << fibonacciIterative(n) << endl;
    return 0;
}
