#ifndef NOEUD_HPP
#define NOEUD_HPP

template <typename T>
class Noeud {
public:
    Noeud<T> *gauche;
    Noeud<T> *droite;
    T data;

    Noeud() : gauche(nullptr), droite(nullptr) {}
    Noeud(const T &data) : gauche(nullptr), droite(nullptr), data(data) {}
    Noeud(const Noeud<T> &that) {
        *this = that;
    }
    Noeud(Noeud<T> &&that) {
        *this = std::move(that);
    }
    virtual ~Noeud() {
        delete gauche;
        delete droite;
    }
    Noeud &operator=(const Noeud<T> &that) {
        this->gauche = that.gauche;
        this->droite = that.droite;
        this->data = that.data;
        return *this;
    }
    Noeud &operator=(Noeud<T> &&that) {
        if(*this!=that) {
            this->gauche = std::move(that.gauche);
            this->droite = std::move(that.droite);
            that.droite = nullptr;
            that.gauche = nullptr;
            this->data = std::move(that.data);
        }
        return *this;
    }
};

#endif