#include <iostream>
using namespace std;

namespace STRING_CONST {
    const int BUFFER_SIZE = 255;
}

class String
{
    
    
private:
    int len;
    char * str;
public:
    String();
    String(const char*);
    String(const String& s);
    ~String();
    
    String& operator=(const String& s);
    String& operator+=(const String& s);
    bool operator==(const String& s);
    String operator+(const String& s);
    
    friend ostream& operator<<(ostream &os, const String& s);
    friend istream& operator>>(istream &os, String& s);
    
};