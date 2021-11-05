#ifndef NOEUD_HPP
#define NOEUD_HPP

template <typename T>
class Noeud {
public:
    Noeud<T> *gauche;
    Noeud<T> *droite;
    T data;
    Noeud() : gauche(nullptr), droite(nullptr) {
        std::cout << "Noeud()" << std::endl;
    }
    Noeud(const T &data) : gauche(nullptr), droite(nullptr), data(data) {
        std::cout << "Noeud(const T &data)" << std::endl;
    }
    Noeud(const Noeud &that) {
        std::cout << "Noeud(const Noeud &that)" << std::endl;
        *this = that;
    }
    Noeud(Noeud &&that) {
        std::cout << "Noeud(Noeud &&that)" << std::endl;
        *this = std::move(that);
    }
    virtual ~Noeud() {
        std::cout << "~Noeud()" << std::endl;
        delete gauche;
        delete droite;
    }
    Noeud &operator=(const Noeud &that) {
        std::cout << "Noeud &operator=(const Noeud &that)" << std::endl;
        this->gauche = that.gauche;
        this->droite = that.droite;
        this->data = that.data;
        return *this;
    }
    Noeud &operator=(Noeud &&that) {
        std::cout << "Noeud &operator=(Noeud &&that)" << std::endl;
        this->gauche = std::move(that.gauche);
        this->droite = std::move(that.droite);
        this->data = std::move(that.data);
        that.droite = nullptr;
        that.gauche = nullptr;
        return *this;
        
    }
};

#endif