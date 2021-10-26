#ifndef NOEUD_HPP
#define NOEUD_HPP

template <typename T>
class Noeud {
public:
    Noeud *gauche;
    Noeud *droite;
    T data;
    Noeud() : gauche(nullptr), droite(nullptr), data(NULL) {}
    Noeud(T data) : gauche(nullptr), droite(nullptr), data(data) {}
    virtual ~Noeud() {
        delete gauche;
        delete droite;
    }
    Noeud &operator=(const Noeud &that) {
        this->gauche = that.gauche;
        this->droite = that.droite;
        this->data = that.data;
    }

    Noeud &operator=(const Noeud &&that) {
        this->gauche = std::move(that.gauche);
        this->droite = std::move(that.droite);
        this->data = std::move(that.data);
    }
};

#endif