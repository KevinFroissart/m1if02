#ifndef NOEUD_HPP
#define NOEUD_HPP

template <typename T>
class Noeud {
public:
    Noeud* gauche;
    Noeud* droite;
    T data;

    // Constructeur par défaut
    Noeud() : gauche(nullptr), droite(nullptr) {}

    Noeud(const T &data) : gauche(nullptr), droite(nullptr), data(data) {}

    // Constructeur par copie
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

    // Opérateur d'assignation par copie
    Noeud &operator=(const Noeud &that) {
        this->data = that.data;
        this->droite = that.droite;
        this->gauche = that.gauche;
        return *this;
    }

    // Opérateur d'assignation par référence
    // Fin du rule of 5
    Noeud &operator=(Noeud &&that) {
        this->data = std::move(that.data);
        this->droite = std::move(that.droite);
        this->gauche = std::move(that.gauche);
        return *this;
    }
};

#endif
