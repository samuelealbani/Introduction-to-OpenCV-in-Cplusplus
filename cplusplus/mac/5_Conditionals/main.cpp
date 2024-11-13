//
//  main.cpp
//  Conditionals
//
//  Created by Samuele Albani on 23/10/2024.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "type \'G\' to start the game, \'E\' to exit: ";
    char user_option = ' ';
    cin>>user_option;
    cout<<"Pressed g";
    
    switch (user_option) {
        case 'g':
            cout << "Game starting...\n";
            break;
            
        default:
            return 0;
            break;
    }
    
    cout << "Guess my float number!\n";
    double my_number = 3.2;
    double guess;
    while (cin >> guess){
        cout << "You typed " << guess << "\n";
        if(guess > my_number) {
            cout << "too big\n";
        } else if (guess < my_number){
            cout << "too small\n";
        } else {
            cout << "got it!\n";
            break;
        }
    }
    
    
    return 0;
}
