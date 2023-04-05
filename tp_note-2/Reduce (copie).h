#include "MyPair.h"
#include "Etiquette.h"

class MyReduceCallback {
    private:
        int VMin;
        int VMaj;
        int CMin;
        int CMaj;
        int Other;

    public:
        MyReduceCallback(const int& VMin_, const int& VMaj_, const int& CMin_, const int& CMaj_, const int& Other_) {
            VMin = VMin_;
            VMaj = VMaj_;
            CMin = CMin_;
            CMaj = CMaj_;
            Other = Other_;
        }

        void operator()(int& agg, MyPair<Etiquette, char> p) {
            switch (p.getFst())
            {
            case Etiquette::VMaj:
                agg += VMaj;
                break;
            case Etiquette::VMin:
                agg += VMin;
                break;
            case Etiquette::CMaj:
                agg += CMaj;
                break;
            case Etiquette::CMin:
                agg += CMin;
                break;
            case Etiquette::Other:
                agg += Other;
            default:
                break;
            }
        }
};

template <typename ResType, typename IteratorInput, typename Callback>
void Reduce(IteratorInput inBeg, IteratorInput inEnd, Callback objetFonction, ResType & agg){
    for(IteratorInput it = inBeg; it != inEnd; it++){
        objetFonction(agg, *it);
    }
}