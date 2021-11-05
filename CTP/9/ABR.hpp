#ifndef ABR_HPP
#define ABR_HPP
#include "Noeud.hpp"
#include <iostream>
#include <deque>

template <typename T>
class ABR {
private:
    Noeud<T> *racine;
    size_t taille;
public:
    ABR() : racine(nullptr), taille(0) {
        std::cout << "ABR()" << std::endl;
    }
    ABR(const ABR &that) {
        std::cout << "ABR(const ABR &that)" << std::endl;
        *this = that;
    }
    ABR(ABR &&that) {
        std::cout << "ABR(ABR &&that)" << std::endl;
        *this = std::move(that);
    }
    ABR &operator=(const ABR &that) {
        std::cout << "ABR &operator=(const ABR &that)" << std::endl;
        this->racine = that.racine;
        this->taille = that.taille;
        return *this;
    }
    ABR &operator=(ABR &&that) {
        std::cout << "ABR &operator=(ABR &&that)" << std::endl;
        this->racine = std::move(that.racine);
        this->taille = that.taille;
        that.racine = nullptr;
        return *this;
    }
    virtual ~ABR() {
        std::cout << "~ABR()" << std::endl;
        delete racine;
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
            if(data < courant->data) {
                courant = courant->gauche;
            } else {
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
        iterator(ABR<T> * arbre, size_t pos) : arbre(arbre), pos(pos) {}
        iterator &operator++(){
            this->pos++;
            return *this;
        }
        iterator &operator--(){
            this->pos--;
            return *this;
        }
        bool operator==(const iterator &that) {
            return this->arbre == that.arbre && this->pos == that.pos;
        }
        bool operator!=(const iterator &that) {
            return !(*this == that);
        }
        const T &operator*(){
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

};

#endif