#include <iostream>
#include <cstring>

class String
{
public:
    String() : string(nullptr), len(0)
    {
        std::cout << "String::String()" << std::endl;
    }
    String(char c) : string(new char(c)), len(1)
    {
        std::cout << "String::String(char)" << std::endl;
    }
    String(const char* c)
    {
        len = strlen(c);
        const size_t length = strlen(c);
        char* tmp_c = new char[length + 1];
        strncpy(tmp_c, c, length);
        string = tmp_c;
        std::cout << "String::String(const char*)" << std::endl;
    }

    const String operator+(const String &c) 
    {    
        String s;
        len = len + c.len;
        s.string = new char[len + 1];
        strcpy(s.string, string);
        strcpy(s.string, c.string);
        return s;
    }

    const String &operator=(const String &s)
    {
        if(this!=&s)
        {
            if(string) delete string;
            string = new char[s.len + 1];
            strcpy(string, s.string);
        }
        return *this;
    }

    /*const String &operator=(String &&s)
    {
        delete string;
        string = s.string;
        s.string = nullptr;
        return *this;
    }*/

    /*
    LaClasse &operator=(LaClasse &&m)
  {
    l = m.l;
    delete ptr;
    ptr = m.ptr;
    m.ptr = nullptr;
    return *this;
  }*/
    
    /*const String &operator=(const String &&s){}
    const bool operator==(const String s){}
    const bool operator!=(const String s){}
    const bool operator<(const String s){}
    const bool operator>(const String s){}
    const bool operator>=(const String s){}
    const bool operator<=(const String s){}*/
    ~String()
    {
        std::cout << "~String()" << std::endl;
        delete string;
    }
private:
    char *string;
    int len;
};      

int main()
{
    String s1;
    String s2('a');
    String s3("a");
    String s4("abc");
    String s5("#]@");
    String s6 = s3 + s4;
    String s7 = s4;

    return 0;
}