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

    // Attentin, le constructeur par déplacement ne doit pas prendre de référence 
    // constante en paramètre, sinon tu ne peux pas effectuer de déplacement, et tu
    // vas simplement faire une copie :)
    ABR(const ABR &&that) {
        // Attention, tu effectues une copie, si tu veux effectuer le déplacement, 
        // il faut faire *this = std::move(that)
        *this = that;
    }
    virtual ~ABR() {
        delete racine;
    }

    ABR &operator=(const ABR &that) {
        // Attention tu copies la valeur du pointeur de l'autre arbre, donc tu as 
        // deux arbre qui ont le même pointeur racine, et donc les mêmes enfants, 
        // donc tu as un risque de double delete. A priori, tu veux effectuer une
        // copie profonde de l'arbre. 
        this->racine = that.racine;
        this->size = that.size;
        return *this;
    }

    // Même remarque que pour le constructeur par déplacement, tu ne dois pas 
    // prendre de référence constante sinon tu ne peux pas modifier l'objet que
    // tu déplaces. Ici tu fais simplement une copie.
    ABR &operator=(const ABR &&that) {
        // A priori tu veux passer la valeur de that.racine à 0 pour éviter les 
        // multiple delete une fois que tu as effectué ton déplacement.
        // Actuellement tu as le même problème que dans ton opérateur de copie, tu
        // vas avoir deux arbres qui ont le même pointeur racine, donc risque de 
        // double delete encore une fois.
        //
        // Aussi, effectuer des move sur that.racine et that.size n'a pas beaucoup
        // d'intérêt parce que ce sont des types primitifs (pointeur et entier), 
        // le déplacement n'a pas de sens pour eux. 
        this->racine = std::move(that.racine);
        this->size = std::move(that.size);
        return *this;
    }

    // Tu devrais passer data par référence constante pour éviter les copies.
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

    // Tu devrais passer data par référence constante pour éviter les copies.
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
        // Original d'utiliser une deque ici, j'aurais plutôt utilisé une pile
        // ou quelque chose dans le genre. Ce n'est pas faux du tout, c'est 
        // simplement surprenant. Un avantage c'est que tu peux remonter dans 
        // l'arbre, un inconvénient c'est que tu vas avoir un coût en mémoire 
        // plus élevé étant donné que tu ne supprimes pas les valeurs de la queue
        // à mesure que tu traverses.
        //
        // Par contre, je ne suis pas convaincu par le fait que tu stockes des T
        // dans ta deque, et non des Noeud<T>*. Le fait qu'un ABR soit une structure
        // en lecture seule justifie certaines décisions de design, mais ici tu 
        // perds un peu en efficacité, étant donné que tu vas effectuer pas mal de 
        // copies, vu que tu stockes des T, et non des T*, T&, ou des Noeud<T>*.
        // Regarde mes commentaires sur ton opérateur* pour plus de détail.
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

        // La fonction n'est pas vraiment optimale ici. Tu renvoies un T, donc tu vas
        // avoir des copies (en plus des copies déjà effectuées que tu as construis ton 
        // deque). Un ABR est read-only, parce que modifier une valeur à la volée sans
        // contrainte poserait pas mal de problèmes pour maintenant la cohérence de la 
        // structure. Mais ça ne veut pas dire que tu dois effectuer des copies en 
        // permanence. Si tu stockes des Noeud<T>* dans ta deque, tu peux tout simplement
        // renvoyer un T const& ici malgré tout, avec return queue[this->pos]->data, ce
        // qui t'évitera une copie et empêchera l'utilisateur de modifier la valeur qu'il
        // obtient.
        T operator*() {
            init(this->tree->racine);
            return queue[this->pos];
        }

        // D'un point de vue objet il serait préférable que cette méthode soit privée
        // au lieu de publique. Ce n'est pas pénalisant, simple conseil de ma part :)
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

    // Tu peux passer une référence constante, voire une rvalue reference pour 
    // améliorer les perfs.
    iterator insert_it(T data) {
        // À quoi sert cette variable au juste ?
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

    // Référence constante pour data :)
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
