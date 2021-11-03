#ifndef ABR_HPP
#define ABR_HPP

template <typename T>
class ABR {
private:
    Noeud<T> *racine;
    size_t pos;
public:

    // Constructeur par défaut
    ABR() : racine(nullptr), pos(0) {}

    // Constructeur par copie
    ABR(const ABR &that) {
        *this = that;
    }

    // Constructeur par référence
    ABR(ABR &&that) {
        *this = std::move(that);
    }

    // Destructeur
    virtual ~ABR() {
        delete racine;
    }

    // Opérateur de copie
    ABR &operator=(const ABR &that) {
        this->racine = new Noeud<T>(that.racine);
        this->pos = that.pos;
        return *this;
    }

    // Opérateur de copie par référence
    ABR &operator=(ABR &&that) {
        if(*this!=that) {
            delete this->racine;
            this->racine = new Noeud<T>(that.racine);
            this->size = that.size;
            that.racine = nullptr;
        }
        return *this;
    }

    void insert(const T &data) {
        Noeud<T> *noeud = new Noeud<T>(data);
        if(this->racine == nullptr) this->racine = noeud;
        else {
            Noeud<T> *courant = this->racine;
            while(courant != noeud) {
                if(data < courant->data) {
                    if(courant->gauche == nullptr) courant->gauche = noeud;
                    courant = courant->gauche;
                } else {
                    if(courant->droite == nullptr) courant->droite = noeud;
                    courant = courant->droite;
                }
            }
        }
    }

    bool find(const T &data) {        
        Noeud<T> *courant = this->racine;
        while(courant != nullptr) {
            if(data == courant->data) return true;
            if(data < courant->data) {
                if(courant->gauche == nullptr) return false;
                courant = courant->gauche;
            } else {
                if(courant->droite == nullptr) return false;
                courant = courant->droite;
            }
        }
        return false;
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const ABR<U> &that);

    std::ostream &print(std::ostream &out, Noeud<T> *noeud) const {
        if(noeud != nullptr) {
            if(noeud->gauche != nullptr) print(out, noeud->gauche);
            out << noeud->data << " ";
            if(noeud->droite != nullptr) print(out, noeud->droite);
        }
        return out;
    }

};

#endif