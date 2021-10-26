#ifndef ABR_HPP
#define ABR_HPP

#include "Noeud.hpp"
#include <deque>

template <typename T>
class ABR {
private:
    Noeud<T> *racine;
    size_t size;
public:
    ABR() : racine(nullptr), size(0) {};
    ABR(const ABR &that) {
        *this = that;
    }
    ABR(const ABR &&that) {
        *this = that;
    }
    virtual ~ABR() {
        delete racine;
    }

    ABR &operator=(const ABR &that) {
        this->racine = that.racine;
        this->size = that.size;
        return *this;
    }

    ABR &operator=(const ABR &&that) {
        this->racine = std::move(that.racine);
        this->size = std::move(that.size);
        return *this;
    }

    void insert(T data) {
        this->size++;
        Noeud<T> *noeud = new Noeud<T>(data);
        if(this->racine == nullptr) this->racine = noeud; 
        else {
            Noeud<T> *courant = racine;
            while(courant != noeud) {
                if(data > courant->data) {
                    if(courant->droite == nullptr) courant->droite = noeud;
                    courant = courant->droite;
                } else {
                    if(courant->gauche == nullptr) courant->gauche = noeud;
                    courant = courant->gauche;
                }
            }
        }
    }

    bool find(T data) const {
        Noeud<T> *courant = racine;
        while(courant != nullptr) {
            if(data == courant->data) return true;
            if(data > courant->data) {
                if(courant->droite == nullptr) return false;
                courant = courant->droite;
            } else {
                if(courant->gauche == nullptr) return false;
                courant = courant->gauche;
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
        const ABR<T> *tree;
        size_t pos;
        std::deque<T> queue;
    public:
        iterator() : tree(nullptr) {};
        iterator(const ABR<T> *tree, size_t pos) : tree(tree), pos(pos) {}
        
        iterator &operator++() {
            this->pos++;
            return *this;
        }

        iterator &operator--() {
            this->pos--;
            return *this;
        }

        bool operator==(const iterator &that) const {
            return this->tree == that.tree && this->pos == that.pos;
        }

        bool operator!=(const iterator &that) const {
            return !(*this == that);
        }

        T operator*() {
            init(this->tree->racine);
            return queue[this->pos];
        }

        void init(const Noeud<T> *noeud) {
            if(noeud != nullptr) {
                if(noeud->gauche != nullptr) init(noeud->gauche);
                queue.push_back(noeud->data);
                if(noeud->droite != nullptr) init(noeud->droite);
            }
        }
    };

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, size);
    }

    iterator insert_it(T data) {
        size_t cpt = 0;
        Noeud<T> *noeud = new Noeud<T>(data);
        if(this->racine == nullptr) this->racine = noeud; 
        else {
            Noeud<T> *courant = racine;
            while(courant != noeud) {
                ++cpt;
                if(data > courant->data) {
                    if(courant->droite == nullptr) courant->droite = noeud;
                    courant = courant->droite;
                } else {
                    if(courant->gauche == nullptr) courant->gauche = noeud;
                    courant = courant->gauche;
                }
            }
        }
        return find_it(data);
    }

    iterator find_it(T data) {
        Noeud<T> *courant = racine;
        while(courant != nullptr) {
            if(data == courant->data) break;
            if(data > courant->data) {
                if(courant->droite == nullptr) break;
                courant = courant->droite;
            } else {
                if(courant->gauche == nullptr) break;
                courant = courant->gauche;
            }
        }
        ABR<int>::iterator it=this->begin();
        ABR<int>::iterator ite=this->end();
        for(;it!=ite;++it)
            if(*it == data) return it;
        return ite;
    }
};

#endif