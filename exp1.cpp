#include <iostream>
using namespace std;

int factorialRecursive(int n) {
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

int factorialIterative(int n) {
    int result = 1; // Initialize result
    for (int i = 1; i <= n; ++i) {
        result *= i; // Calculate factorial
    }
    return result; // Return the result
}
int main() {
    int number;
    cout << "Enter a number to find its factorial: ";
    cin >> number;
    if (number < 0) {
        cout << "Factorial of a negative number doesn't exist." << endl;
    } else {
        cout << "Factorial of " << number << " using recursion is: " << factorialRecursive(number) << endl;
        cout << "Factorial of " << number << " using iteration is: " << factorialIterative(number) << endl;
    }
    return 0;
}
