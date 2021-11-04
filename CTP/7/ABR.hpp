#ifndef ABR_HPP
#define ABR_HPP
#include "Noeud.hpp"
#include <deque>

template <typename T>
class ABR {
private:
    Noeud<T> *racine;
    size_t taille;

public:
    ABR() : racine(nullptr), taille(0) {}
    ABR(const ABR &that) {
        *this = that;
    }
    ABR(ABR &&that) {
        *this = std::move(that);
    }
    virtual ~ABR() {
        delete racine;
    }
    ABR &operator=(const ABR &that) {
        this->racine = new Noeud<T>(that.racine);
        this->taille = that.taille;
        return *this;
    }
    ABR &operator=(ABR &&that) {
        if(*this!=that) {
            delete racine;
            this->racine = std::move(new Noeud<T>(that.racine));
            this->taille = std::move(that.taille);
            that.racine = nullptr;
        }
        return *this;
    }

    void insert(const T &data) {
        this->taille++;
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
            if(courant->data == data) return true;
            if(data > courant->data) {
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
    friend std::ostream &operator<<(std::ostream &out, const ABR<U> &arbre);

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
        iterator &operator++() {
            this->pos++;
            return *this;
        }
        iterator &operator--() {
            this->pos--;
            return *this;
        }
        bool operator==(const iterator &that) {
            return this->arbre == that.arbre && this->pos == that.pos;
        }
        bool operator!=(const iterator &that) {
            return !(*this == that);
        }
        const T &operator*() {
            init(this->arbre->racine);
            return queue[this->pos]->data;
        }
    };

    iterator begin() {
        return iterator(this, 0);
    }
    iterator end() {
        return iterator(this, this->taille);
    }

    iterator insert_it(const T &data) {
        this->taille++;
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
        return find_it(data);   
    }

    iterator find_it(const T &data) {
        ABR<int>::iterator it=begin();
        ABR<int>::iterator ite=end();
        for(;it!=ite;++it)
            if(*it == data) return it;
        return ite;
    }
};

#endif