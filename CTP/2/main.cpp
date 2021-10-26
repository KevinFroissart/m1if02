#include <iostream>
#include <cstdlib>
#include <deque>

template <typename T>
class Noeud {
private:
public:
    Noeud() : gauche(nullptr), droite(nullptr), data(NULL) {}
    Noeud(T data) : gauche(nullptr), droite(nullptr), data(data) {}
    Noeud<T> *gauche;
    Noeud<T> *droite;
    T data;
};

template <typename T>
class ABR {
private:
    Noeud<T> *racine;
    int nb_element;
public:
    ABR() : racine(nullptr), nb_element(0) {}

    ABR(const ABR &that) {
        this = that;
    }

    ABR(const ABR &&that) {
        this = that;
    }

    ABR &operator=(const ABR &that) {
        this->racine = that.racine;
        this->nb_element = that.nb_element;
        return *this;
    }

    ABR &operator=(const ABR &&that) {
        this->racine = std::move(that.racine);
        this->nb_element = std::move(that.nb_element);
        return *this;
    }

    virtual ~ABR() {
        delete racine;
    }

    void insert(T data) {
        this->nb_element++;
        Noeud<T> *n = new Noeud<T>(data);

        if(this->racine == nullptr) this->racine = n;
        else {
            Noeud<T> *courant = this->racine;
            while(courant != n) {
                if(n->data > courant->data) {
                    if(courant->droite == nullptr) courant->droite = n;
                    else courant = courant->droite;
                } else {
                    if(courant->gauche == nullptr) courant->gauche = n;
                    else courant = courant->gauche;
                }
            }
        }
    }

    // void insert_op(T data) {
    //     this->nb_element++;
    //     Noeud<T> *n = new Noeud<T>(data);

    //     if(this->racine == nullptr) this->racine = n;
    //     else {
    //         Noeud<T> *courant = this->racine;
    //         while(courant != n) {
    //             if(n->data > courant->data) {
    //                 if(courant->droite == nullptr) courant->droite = n;
    //                 else courant = courant->droite;
    //             } else {
    //                 if(courant->gauche == nullptr) courant->gauche = n;
    //                 else courant = courant->gauche;
    //             }
    //         }
    //     }

    //     ABR<T>::const_iterator it=this.begin();
    //     ABR<T>::const_iterator ite=this.end();
    //     for(;it!=ite;++it)
    //         if(*it == data) return const_iterator(this, it.pos);
    // }

    bool find(T data) {        
        Noeud<T> *courant = this->racine;
        while(courant != nullptr) {
            if(courant->data == data) return true;
            if(data > courant->data) {
                courant = courant->droite;
            } else {
                courant = courant->gauche;
            }
        }
        return false;
    }

    std::ostream &print(std::ostream &out, Noeud<T> *n) const{
        if(n != nullptr) {
            if(n->gauche != nullptr) print(out, n->gauche);
            out << n->data << " ";
            if(n->droite != nullptr) print(out, n->droite);
        }
        return out;
    }
    
    template <typename U>
    friend std::ostream &operator<<(std::ostream &outgoing, const ABR<U> &other);

    class const_iterator // Nested class : SimpQue<int, 5>::iterator. Ca ne vous rappelle pas les vector par exemple ? ;)
        // Les nested class sont automatiquement amies de leur classe parente.
        {
            private:
                const ABR<T> *tree;
                size_t pos;
                std::deque<T> queue;

            public:
                const_iterator()
                {
                    this->tree = nullptr;
                }

                const_iterator(ABR<T> *tree, size_t pos)
                {
                    this->tree = tree;
                    this->pos = pos;
                }

                const_iterator &operator++() // Pas de parametre = Prefixe (++it)
                {
                    this->pos++;
                    return *this;
                }

                const_iterator operator++(int unused) // Parametre entier = Postfixe (it++) (convention)
                {
                    // il faut retourner notre etat avant modification donc faire une copie
                    const_iterator it2 = *this;
                    this->pos++;
                    return it2; // attention on retourne une variable locale, donc pas en reference !
                }

                void init(Noeud<T> *n) {
                    if(n != nullptr) {
                        if(n->gauche != nullptr) init(n->gauche);
                        this->queue.push_back(n->data);
                        if(n->droite != nullptr) init(n->droite);
                    }
                }

                T &operator*() 
                {
                    if (this->tree == nullptr)
                        throw std::logic_error("Iterator uninitialized");
                    this->init(this->tree->racine);
                    return this->queue[pos];
                }

                bool operator==(const const_iterator &that) const
                {
                    return this->tree == that.tree && this->pos == that.pos;
                }

                bool operator!=(const const_iterator &that) const
                {
                    return !(*this == that); // copier du code c'est mal. different = !(egal)
                }
        };

        const_iterator begin()
        {
            return const_iterator(this, 0); // le debut, c'est l'index 0 de la SimpQue
        }

        // la fin, ce n'est pas le dernier element mais en fait "un cran apres", cad. le moment
        // ou l'iterateur commence a etre invalide
        // il sert de condition d'arret a l'utilisation (++it tant que it != container.end()), cf. main
        const_iterator end()
        {
            return const_iterator(this, this->nb_element); // donc pas size-1 mais bien size
        }

};

template <typename U>
std::ostream &operator<<(std::ostream &outgoing, const ABR<U> &other)
{
    return other.print(outgoing, other.racine);
}


int main() {

    ABR<int> tree;
    for(int i=0;i<10;i++)
         tree.insert(rand() % 100); // #include<cstdlib>

    std::cout << tree << std::endl; // Affichage infixé
    while(!tree.find(rand() % 100));

    ABR<int>::const_iterator it=tree.begin();
    ABR<int>::const_iterator ite=tree.end();
    for(;it!=ite;++it)
        std::cout << *it << std::endl;

    return 0;
}