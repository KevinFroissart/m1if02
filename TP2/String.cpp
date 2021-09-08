#include <iostream>
#include <cstring>

class String
{
public:
    String() : string(nullptr)
    {
        std::cout << "String::String()" << std::endl;
    }
    String(char c) : string(new char(c))
    {
        std::cout << "String::String(char)" << std::endl;
    }
    String(const char* c)
    {
        const size_t len = strlen(c);
        char* tmp_c = new char[len + 1];
        strncpy(tmp_c, c, len);
        string = tmp_c;
        std::cout << "String::String(const char*)" << std::endl;
    }
    const String &operator=(const String &s)
    {
        string = new char(s.string);
    }
    /*const String &operator=(const String &&s){}
    const String operator+(const String s){}
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
};      

int main()
{
    String s1;
    String s2('a');
    String s3("a");
    String s4("abc");
    String s5("#]@");
}