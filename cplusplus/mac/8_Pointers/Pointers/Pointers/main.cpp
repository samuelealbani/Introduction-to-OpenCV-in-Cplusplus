//
//  main.cpp
//  Pointers
//
//  Created by Samuele Albani on 31/10/2024.
//

#include <iostream>
using namespace std;

int var = 16;
int* ptr = &var;    // ptr holds the address of var

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << ptr << endl;
    cout << *ptr << endl; // returns the content of the ptr address
    return 0;
}
