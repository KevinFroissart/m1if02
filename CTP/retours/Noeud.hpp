#ifndef NOEUD_HPP
#define NOEUD_HPP

// Attention, tu ne respectes pas le Rule of 5, et au vu de ton code dans
// Arbre.hpp, ça peut être très problématique. Il te manque un constructeur
// par copie et un constructeur par déplacement.
template <typename T>
class Noeud {
public:
    Noeud *gauche;
    Noeud *droite;
    T data;
    Noeud() : gauche(nullptr), droite(nullptr), data(NULL) {}
    // Tu peux avoir une version avec référence constante pour éviter la copie 
    // au moment du passage de paramère, et une version par rvalue-reference pour
    // permettre un move de la valeur, afin d'améliorer les perfs si tu as un arbre
    // qui stocke des valeurs pour lesquelles move est intéressant.
    Noeud(T data) : gauche(nullptr), droite(nullptr), data(data) {}
    virtual ~Noeud() {
        delete gauche;
        delete droite;
    }

    // Mêmes remarques pour les opérateurs de copie et de déplacement, ton
    // opérateur de copie doit effectuer une copie profonde, et non une 
    // copie de pointeurs (problèmes de mémoire), et ton opérateur de déplacement
    // ne doit pasp rendre de référence constante en paramètre parce qu'il 
    // faut à priori modifier les pointeurs de that pour les passer à 0.
    //
    // Attention, dans les deux cas tu as oublié de faire le return *this de 
    // rigueur.

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
