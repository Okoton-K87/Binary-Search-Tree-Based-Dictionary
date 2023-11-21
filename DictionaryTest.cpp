//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// An alternate test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {

    string s;
    int x;
    string words[] = {
        "typography",
        "pixel",
        "algorithm",
        "data",
        "design",
        "encryption",
        "hardware",
        "internet",
        "javascript",
        "kernel"
    };

    string removeWords[] = {
        "pixel",
        "encryption",
        "internet"
    };

    cout << "Test: Dictionary Creation======================" << endl;

    Dictionary D;

    // insert some pairs into D
    for(int i=0; i<10; i++){
        D.setValue(words[i], i+1);
    }

    cout << "D.size() = " << D.size() << endl;
    cout << D << endl;

    cout << "Test: Copy and Assignment======================" << endl;

    // Call copy constructor
    Dictionary E = D;

    // Call operator=()
    Dictionary F;
    F = D;

    cout << "E.size() = " << E.size() << endl;
    cout << "F.size() = " << F.size() << endl;
    cout << "D==E is " << (D==E?"true":"false") << endl;
    cout << "D==F is " << (D==F?"true":"false") << endl;

    cout << "Test: Modification and Comparison======================" << endl;

    // modify D
    D.setValue("kernel", 100);
    cout << "D==E is " << (D==E?"true":"false") << endl;
    cout << "D==F is " << (D==F?"true":"false") << endl;

    cout << "Test: Forward and Reverse Iteration======================" << endl;

    // forward iteration on D
    for(D.begin(); D.hasCurrent(); D.next()){
        s = D.currentKey();
        x = D.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl << endl;

    // reverse iteration on D
    for(D.end(); D.hasCurrent(); D.prev()){
        s = D.currentKey();
        x = D.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl << endl;

    cout << "Test: Removal and Exception Handling======================" << endl;

    // remove some pairs from D and check exception handling
    for(int i=0; i<3; i++){
        try{
            cout << "Removing " << removeWords[i] << " from Dictionary D" << endl; 
            D.remove(removeWords[i]);
        } catch(logic_error& e){
            cout << e.what() << endl;
            cout << "   continuing without interruption" << endl;
        }
    }

    cout << "D.size() = " << D.size() << endl;
    cout << D << endl;

    return(EXIT_SUCCESS);
}
