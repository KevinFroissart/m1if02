#include <iostream>
#include <deque>

template <typename T>
class Noeud {
private:
public:
    T data;
    Noeud *gauche;
    Noeud *droite;

    Noeud() : gauche(nullptr), droite(nullptr), data(NULL) {}
    Noeud(T data) : gauche(nullptr), droite(nullptr), data(data) {}
    virtual ~Noeud() {
        delete gauche;
        delete droite;
    }
};

template <typename T>
class ABR {
private:
    Noeud<T> *racine;
    size_t size;
public:
    ABR() : racine(nullptr), size(0) {}
    ABR(const ABR &that) {
        this = that;
    }
    ABR(const ABR &&that) {
        this = that;
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

    virtual ~ABR() {
        delete racine;
    }

    void insert(T data) {
        this->size++;
        Noeud<T> *noeud = new Noeud<T>(data);
        if(racine == nullptr) racine = noeud;
        else {
            Noeud<T> *courant = racine;
            while(courant != noeud) {
                if(data > courant->data) {
                    if(courant->droite == nullptr) courant->droite = noeud;
                    else courant = courant->droite;
                }
                else {
                    if(courant->gauche == nullptr) courant->gauche = noeud;
                    else courant = courant->gauche;
                }
            }
        }
    }

    bool find(T data) {
        Noeud<T> *courant = racine;
        while(courant != nullptr) {
            if(data == courant->data) return true;
            if(data > courant->data) {
                if(courant->droite == nullptr) return false;
                else courant = courant->droite;
            }
            else {
                if(courant->gauche == nullptr) return false;
                else courant = courant->gauche;
            }
        }
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &outgoing, const ABR<U> &other);

    std::ostream &print(std::ostream &out, Noeud<T> *n) const{
        if(n != nullptr) {
            if(n->gauche != nullptr) print(out, n->gauche);
            out << n->data << " ";
            if(n->droite != nullptr) print(out, n->droite);
        }
        return out;
    }

    class iterator {
    private:
        const ABR<T> *tree;
        size_t pos;
        std::deque<T> queue;
    public:
        iterator() : tree(nullptr) {}
        iterator(ABR<T> *tree, size_t pos) : tree(tree), pos(pos) {}

        iterator &operator++() {
            this->pos++;
            return *this;
        }

        void init(const Noeud<T> *n) {
            if(n != nullptr) {
                if(n->gauche != nullptr) init(n->gauche);
                queue.push_back(n->data);
                if(n->droite != nullptr) init(n->droite);
            }
        }

        T &operator*() {
            init(this->tree->racine);
            return this->queue[this->pos];
        }

        bool operator==(const iterator &that) const {
            return this->tree == that.tree && this->pos == that.pos;
        }

        bool operator!=(const iterator &that) const {
            return !(*this == that);
        }
    };

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, size);
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

    ABR<int>::iterator it=tree.begin();
    ABR<int>::iterator ite=tree.end();
    for(;it!=ite;++it)
        std::cout << *it << std::endl;

    return 0;
}