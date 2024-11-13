//
//  main.cpp
//  Operators
//
//  Created by Samuele Albani on 22/10/2024.
//

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    string my_name = "Samuele";
    string greeting = "Hello, " + my_name; // concatenation
    cout << greeting << "\n";
    
    int my_num = 23;
    int plus_one = ++my_num ; // my_num + 1
    cout << plus_one<<"\n";
    
    plus_one+=4;
    cout << plus_one << "\n";
    
    int decrement = --plus_one;
    cout << decrement << "\n";
    
    return 0;
}
