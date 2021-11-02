#ifndef NOEUD_HPP
#define NOEUD_HPP

template <typename T>
class Noeud {
public:
    Noeud* gauche;
    Noeud* droite;
    T data;

    Noeud() : gauche(nullptr), droite(nullptr) {}
    Noeud(const T &data) : gauche(nullptr), droite(nullptr), data(data) {}
    Noeud(const Noeud &that) {
        *this = that;
    }
    Noeud(Noeud &&that) {
        *this = std::move(that);
    }
    virtual ~Noeud() {
        delete gauche;
        delete droite;
    }
    Noeud &operator=(const Noeud &that) {
        this->data = that.data;
        this->droite = that.droite;
        this->gauche = that.gauche;
        return *this;
    }
    Noeud &operator=(Noeud &&that) {
        this->data = std::move(that.data);
        this->droite = std::move(that.droite);
        this->gauche = std::move(that.gauche);
        return *this;
    }
};

#endif
