#include <iostream>

using namespace std;

int main() {
    double num1, num2;
    char operation;
    
    cout << "Welcome to the basic calculator!" << endl;
    
    // Input the first number
    cout << "Enter the first number: ";
    cin >> num1;
    
    // Input the operator
    cout << "Enter the operation (+, -, *, /): ";
    cin >> operation;
    
    // Input the second number
    cout << "Enter the second number: ";
    cin >> num2;
    
    // Perform the selected operation
    switch (operation) {
        case '+':
            cout << "Result: " << num1 << " + " << num2 << " = " << (num1 + num2) << endl;
            break;
        case '-':
            cout << "Result: " << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
            break;
        case '*':
            cout << "Result: " << num1 << " * " << num2 << " = " << (num1 * num2) << endl;
            break;
        case '/':
            // Handle division by zero
            if (num2 != 0) {
                cout << "Result: " << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
            } else {
                cout << "Error: Division by zero is not allowed." << endl;
            }
            break;
        default:
            // Handle invalid operator
            cout << "Error: Invalid operation!" << endl;
    }

    return 0;
}