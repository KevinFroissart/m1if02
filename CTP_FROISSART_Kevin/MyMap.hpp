#ifndef MYMAP_HPP
#define MYMAP_HPP

#include <iostream>

template <typename IteratorInput, typename IteratorOutput, typename CallBack>
void Map(IteratorInput inBeg, IteratorInput inEnd, IteratorOutput outpos, CallBack objetFonction) {
    for(; inBeg != inEnd; inBeg++, outpos++) {
        *outpos = objetFonction(*inBeg);
    }
}


#endif