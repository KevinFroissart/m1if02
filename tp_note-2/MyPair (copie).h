
#ifndef MYPAIR
#define MYPAIR

template<typename T1, typename T2>
class MyPair
{
private:
    T1 first;
    T2 second;
public:
    MyPair(const T1& first_, const T2& second_) : first(first_), second(second_) {};
    MyPair(const MyPair& other) : first(other.first), second(other.second) {};

    MyPair& operator=(const MyPair& other){
        first = other.first;
        second = other.second;
        return *this;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const MyPair &pair) {
        os << " fst: " << pair.first << " snd: " << pair.second << "\n";
        return os;
    }

    T1 getFst(){
        return first;
    }

    T2 getSnd(){
        return second;
    }

    ~MyPair() = default;
};

template<typename T1, typename T2>
MyPair<T1, T2> makeMyPair(const T1& first_, const T2& second_){
    return MyPair<T1, T2>(first_, second_);
}

#endif
