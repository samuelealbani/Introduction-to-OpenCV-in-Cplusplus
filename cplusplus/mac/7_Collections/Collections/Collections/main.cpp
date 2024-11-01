//
//  main.cpp
//  Collections
//
//  Created by Samuele Albani on 31/10/2024.
//

#include <iostream>

using namespace std;

vector<int> my_numbers = {23, 4, 159, 2};

vector<string> my_friends = {"Jake", "Yuan", "Gino"};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    cout << my_numbers.size() << endl;
    
    for(int i = 0; i<my_numbers.size(); ++i){
        cout << my_numbers[i] << endl;
    }
    
    my_friends.push_back("Valentino");
    for(int i = 0; i<my_friends.size(); ++i){
        cout << my_friends[i] << endl;
    }
    
    return 0;
}
