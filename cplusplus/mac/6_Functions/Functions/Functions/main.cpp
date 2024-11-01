//
//  main.cpp
//  Functions
//
//  Created by Samuele Albani on 31/10/2024.
//

#include <iostream>
#include <string>

using namespace std;

void say_hello(string name){
    cout << "Hello, " << name << "\n";
}

int plus_one(int x){
    return x+1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string your_name;
    cout << "What's your name? ";
    cin>>your_name;
    say_hello(your_name);
    
    cout << "Type an integer: ";
    int input;
    cin>>input;
    cout << input << " + 1 = " << plus_one(input) << "\n";
    
    return 0;
}
