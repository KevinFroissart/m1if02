#ifndef MYPAIR_HPP
#define MYPAIR_HPP

template <typename T, typename U>
class MyPair {
private:
public:
    T first;
    U second;

    MyPair() {
        //std::cout << "Mypair()" << std::endl;
    }
    MyPair(const T &first, const U &second) {
        //std::cout << "MyPair(const T &first, const U &second)" << std::endl;
        this->first = first;
        this->second = second;
    }
    MyPair(const MyPair &that) {
        //std::cout << "MyPair(const MyPair &that)" << std::endl;
        *this = that;
    }
    MyPair(MyPair &&that) {
        //std::cout << "MyPair(MyPair &&that)" << std::endl;
        *this = std::move(that);
    }
    virtual ~MyPair() {
        //std::cout << "~MyPair()" << std::endl;
    }
    MyPair &operator=(const MyPair &that) {
        //std::cout << "MyPair &operator=(const MyPair &that)" << std::endl;
        this->first = that.first;
        this->second = that.second;
        return *this;
    }
    MyPair &operator=(MyPair &&that) {
        //std::cout << "MyPair &operator=(MyPair &&that)" << std::endl;
        this->first = std::move(that.first);
        this->second = std::move(that.second);
        return *this;
    }

    template <typename X, typename Y>
    friend MyPair<X,Y> makeMyPair(const X &first, const Y &second);
};

#endif