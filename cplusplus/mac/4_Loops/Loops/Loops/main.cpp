//
//  main.cpp
//  Loops
//
//  Created by Samuele Albani on 22/10/2024.
//

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[]) {
    // insert code here...
    cout << "Type some names:\n";
    string name;
    while (cin >> name) {
        cout << "Hello, " << name;
        
        for(int i=0; i < 3; ++i){
            cout << ' ' << i ;
        }
        
        cout << "\n";
    }

    return 0;
}
