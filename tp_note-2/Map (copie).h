#include "MyPair.h"
#include "Etiquette.h"

class MyMapCallback {

    public:
        MyMapCallback(bool min_) : min(min_) {};
        MyPair<Etiquette, char> operator()(const char& c){
            Etiquette e;
            if(c >= 'a' && c <= 'z'){
                e = Etiquette::CMin;
            }
            else if(c >= 'A' && c <= 'Z'){
                e = Etiquette::CMaj;
            }
            else {
                e = Etiquette::Other;
            }

            if(e != Etiquette::Other){
                switch(c){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                    case 'y':
                        e = Etiquette::VMin;
                        break;
                    case 'A':
                    case 'E':
                    case 'I':
                    case 'O':
                    case 'U':
                    case 'Y':
                        e = Etiquette::VMaj;
                        break;
                }
            }

            char d = c;
            if(min && c >= 'A' && c <= 'Z'){
                d = c - 'A' + 'a';
            }
            return MyPair<Etiquette, char>(e, d);
        }

    private:
        bool min;
};

Etiquette getEtiquette(const char& c){
    Etiquette e;
    if(c >= 'a' && c <= 'z'){
        e = Etiquette::CMin;
    }
    else if(c >= 'A' && c <= 'Z'){
        e = Etiquette::CMaj;
    }
    else {
        e = Etiquette::Other;
    }

    if(e != Etiquette::Other){
        switch(c){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'y':
                e = Etiquette::VMin;
                break;
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
            case 'Y':
                e = Etiquette::VMaj;
                break;
        }
    }
    return e;
}

template <typename IteratorInput, typename IteratorOutput, typename Callback>
void Map(IteratorInput inBeg, IteratorInput inEnd, IteratorOutput outpos, Callback objetFonction) {
    for(IteratorInput it = inBeg; it != inEnd; it++, outpos++){
        *outpos = objetFonction(*it);
    }
}