//
//  String.cpp
//  YoonC_chap4
//
//  Created by Paul on 2015. 10. 7..
//  Copyright (c) 2015년 Paul. All rights reserved.
//

#include <cstring>
#include <iostream>
#include "String.h"
using namespace std;

//general func
ostream& operator<<(ostream &os , const String& s)
{
    os << s.str;
    return os;
}

istream& operator>>(istream &is, String& s)
{
    if(s.str != NULL)
        delete[] s.str;
    char l_str[STRING_CONST::BUFFER_SIZE];
    is >> l_str;
    s.len = (int)strlen(l_str);
    s.str = new char[s.len+1];
    strcpy(s.str, l_str);
    return is;
}

//member function
String::String()
{
    len = 0;
    str = new char[1];
    str[0] = '\0';
}

String::String(const char* l_str)
{
    len = (int)strlen(l_str);
    str =  new char[len+1];
    strcpy( str, l_str);
}

String::String(const String &s)
{
    len = s.len;
    str = new char[len+1];
    strcpy(str, s.str);
}

String::~String()
{
    delete[] str;
}

String& String::operator=(const String &s)
{
    len = s.len;
    if(s.str != NULL)
        delete[] str;
    str = new char[len+1];
    strcpy(str, s.str);
    
    return *this;
}

String& String::operator+=(const String &s)
{
    char * tmp = new char[len+s.len+1];
    strcpy(tmp, str);
    strcat(tmp, s.str);
    len += s.len;
    if( str != NULL)
        delete []str;
    str = tmp;
    return *this;
}

bool String::operator==(const String &s)
{
    if(len != s.len)
        return false;
    if(strcmp(str, s.str) != 0 )
        return false;
    return true;
}

String String::operator+(const String &s)
{
    String new_str(*this);
    new_str += s;
    return new_str;
}