//
//  main.cpp
//  YoonC_chap4
//
//  Created by Paul on 2015. 10. 4..
//  Copyright (c) 2015년 Paul. All rights reserved.
//

#include <iostream>
#include "String.h"
using namespace std;

int main (){
    String s1("abc");
    String s2("def");
    
    cout<< "s1="<< s1 << endl;
    cout<< "s2="<< s2 << endl;
    
    cout << "s1+s2=" << s1+s2<< endl;
    
    s1+= s2;
    cout << "s1+=s2" << endl;
    
    cout << "s1=" << s1 << endl;
    
    cout << "s1 : ";
    cin >> s1;
    cout << "s2 : ";
    cin >> s2;
    
    cout << "s1=" << s1 <<endl;
    cout << "s2=" << s2 << endl;
    
    if( s1 == s2)
        cout << s1 << "==" << s2 << endl;
    else
        cout << s1 << "!=" << s2 << endl;
    return 0;
}
