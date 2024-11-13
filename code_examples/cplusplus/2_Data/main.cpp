//
//  main.cpp
//  Data
//
//  Created by Samuele Albani on 22/10/2024.
//

//Header files add functionality to C++ programs.


#include <iostream> // library that lets us work with input and output objects

#include <string> // the string library

using namespace std; // means that we can use names for objects and variables from the standard library.

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Please enter your first name: ";
    
    string first_name;
    cin >> first_name;
    
    cout << "Hello, " << first_name << "!\n";
    
    int age = 26;
    double weigth = 70.5;
    string my_name = "Samuele";
    char initial = 'S';
    bool is_funny = true;
    
    
    return 0; // ends the main function.
}
