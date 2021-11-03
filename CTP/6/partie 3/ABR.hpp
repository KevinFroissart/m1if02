#ifndef ABR_HPP
#define ABR_HPP
#include <deque>

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

    class iterator {
    private:
        ABR<T> *arbre;
        size_t pos;
        std::deque<Noeud<T>*> queue;

        void init(Noeud<T> *noeud) {
            if(noeud != nullptr) {
                if(noeud->gauche != nullptr) init(noeud->gauche);
                queue.push_back(noeud);
                if(noeud->droite != nullptr) init(noeud->droite);
            }
        }
    public:
        iterator() : arbre(nullptr), pos(0) {}
        iterator(ABR<T> *arbre, size_t pos) : arbre(arbre), pos(pos) {}
        bool operator==(const iterator &that) {
            return this->arbre == that.arbre && this->pos == that.pos;
        } 
        bool operator!=(const iterator &that) {
            return !(*this == that);
        }
        iterator &operator++() {
            this->pos++;
            return *this;
        }
        iterator &operator--() {
            this->pos--;
            return *this;
        }
        const T &operator*() {
            this->init(this->arbre->racine);
            return queue[this->pos]->data;
        }
    };

    iterator begin(){
        return iterator(this, 0);
    }

    iterator end(){
        return iterator(this, this->pos);
    }

    iterator insert(const T &data) {
        this->pos++;
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
        return find(data);
    }

    iterator find(const T &data) {        
        ABR<int>::iterator it=begin();
        ABR<int>::iterator ite=end();
            for(;it!=ite;++it)
                if(*it == data) return it;
        return ite;
    }


};

#endif