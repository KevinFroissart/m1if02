#ifndef NOEUD_HPP
#define NOEUD_HPP

template <typename T>
class Noeud {
public:
    Noeud<T> *gauche;
    Noeud<T> *droite;
    T data;

    // Constructeur par défaut
    Noeud() : gauche(nullptr), droite(nullptr) {}

    // Constructeur avec parametre
    Noeud(const T &data) : gauche(nullptr), droite(nullptr), data(data) {}

    // Constructeur de copie
    Noeud(const Noeud &that) {
        *this = that;
    }

    // Constructeur par référence
    Noeud(Noeud &&that) {
        *this = std::move(that);
    }

    // Destructeur
    virtual ~Noeud() {
        delete gauche;
        delete droite;
    }

    // Opérateur de copie
    Noeud &operator=(const Noeud &that) {
        this->gauche = that.gauche;
        this->droite = that.droite;
        this->data = that.data;
        return *this;
    }

    // Opérateur de copie par référence
    Noeud &operator=(Noeud &&that) {
        this->gauche = std::move(that.gauche);
        this->droite = std::move(that.droite);
        this->data = std::move(that.data);
        return *this;
    }
};

#endif