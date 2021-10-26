#ifndef __SIMPQUE_HPP__
#define __SIMPQUE_HPP__

#include <iostream>
#include <stdexcept>
#include "Wagon.hpp"

template <typename T, size_t CapacityWagons>
class SimpQue
{
    private:
        Wagon<T, CapacityWagons> *first;
        Wagon<T, CapacityWagons> *last;

    public:
        // Constructeur par defaut cree un premier wagon vide. Cela simplifie la gestion
        // surtout qu'il y a peu de chance pour que quelqu'un cree une SimpQue pour finalement
        // ne pas l'utiliser du tout
        SimpQue() : first(new Wagon<T, CapacityWagons>), last(first)
        {
        }

        // Constructeur par copie
        SimpQue(const SimpQue &that)
        {
            this->first = nullptr;
            *this = that; // copier-coller du code c'est mal. le boulot est fait dans l'operator= :)

            // le first=nullptr informe l'operator= de ne pas faire son delete
        }

        // Constructeur a partir d'un tableau C
        SimpQue(const T *array, size_t size) : first(new Wagon<T, CapacityWagons>), last(first)
        {
            for (size_t i = 0; i < size; i++)
                this->add(array[i]);
        }

        virtual ~SimpQue()
        {
            delete first;
            // grace a la recursivite du destructeur de Wagon toute la chaine sera detruite.
            // on ne fait donc pas delete last !
        }

        SimpQue &operator=(const SimpQue &that)
        {
            // on supprime ce qu'on avait (meme remarque que pour le destructeur)
            if (first != nullptr)
                delete first;

            // puis on se copie a l'autre.
            // il faut cloner tous les wagons, et les relier entre eux pour faire notre propre chaine a nous
            // c'est la fonction qui m'a pris le plus de temps de reflexion
            // comme quoi on pouvait arracher pas mal de points meme sans la faire...
            if (that.first != nullptr) // ne devrait pas etre possible a cause du constructeur par defaut qui en fait tjs un...
            {
                this->first = new Wagon<T, CapacityWagons>(*that.first); // Copie du premier wagon dans first

                // Variables de boucle
                Wagon<T, CapacityWagons> *cur = this->first; // Attention entre notre chaine locale...
                Wagon<T, CapacityWagons> *next = that.first->getNext(); // et la chaine originale !

                while (next != nullptr)
                {
                    cur->setNext(new Wagon<T, CapacityWagons>(*next));
                    cur = cur->getNext();
                    next = next->getNext();
                }
                this->last = cur;
            }
            return *this;
        }

        SimpQue &add(const T &elem)
        {
            // Gestion des wagons incomplets
            Wagon<T, CapacityWagons> *tmp = first;

            while (tmp != nullptr && tmp->isFull())
                tmp = tmp->getNext();

            if (tmp == nullptr)
            {
                // Nouveau wagon
                Wagon<T, CapacityWagons> *w = new Wagon<T, CapacityWagons>();
                w->add(elem);
                this->last->setNext(w);
                this->last = w;
            }
            else
                // tmp est un wagon avec de la place
                tmp->add(elem);

            return *this;
        }

        // operator d'acces avec modification, sert en tant que lvalue
        T &operator[](size_t index)
        {
            // Gestion des wagons incomplets, on ne peut pas simplement de decaler de index modulo CapacityWagons !
            Wagon<T, CapacityWagons> *tmp = first;

            while (tmp != nullptr && index >= tmp->getSize())
            {
                index -= tmp->getSize();
                tmp = tmp->getNext();
            }

            if (tmp == nullptr) // l'index est plus grand que le nombre effectif d'elements dans la liste
                throw std::overflow_error("Out of bounds");

            // index < tmp->getSize() donc l'element qu'on cherche est dans le wagon tmp
            return tmp->get(index);
        }

        // operateur d'acces constant... sert en tant que rvalue
        const T &operator[](size_t index) const
        {
            // meme algo que l'operateur avec modification
            Wagon<T, CapacityWagons> *tmp = first;

            while (tmp != nullptr && index >= tmp->getSize())
            {
                index -= tmp->getSize();
                tmp = tmp->getNext();
            }

            if (tmp == nullptr)
                throw std::overflow_error("Out of bounds");

            return tmp->get(index);
        }

        size_t getSize() const
        {
            // soit on cache la taille dans une variable privee qu'on met a jour lors des
            // insertions et suppressions, mais on a
            // un probleme de conception (cf. donnees redondantes en base de donnees ;))
            // soit on perd un peu de perf en parcourant la liste.

            size_t s = 0;

            Wagon<T, CapacityWagons> *w = this->first;
            while (w != nullptr)
            {
                s += w->getSize();
                w = w->getNext();
            }

            return s;
        }

        // ce n'est PAS une declaration fonction membre mais une simple declaration de fonction separee mais
        // "amie" qui aura donc le droit de taper dans nos variables privees.
        // Cette declaration ne connait donc pas nos parametres T et CapacityWagons.
        // Il faut la declarer en template (avec d'autres noms de parametres)
        template <typename U, size_t SW>
        friend std::ostream &operator<<(std::ostream &outgoing, const SimpQue<U, SW> &other);

        class const_iterator // Nested class : SimpQue<int, 5>::iterator. Ca ne vous rappelle pas les vector par exemple ? ;)
        // Les nested class sont automatiquement amies de leur classe parente.
        {
            private:
                const SimpQue<T, CapacityWagons> *sq;
                size_t pos;

            public:
                const_iterator()
                {
                    this->sq = nullptr;
                }

                const_iterator(SimpQue<T, CapacityWagons> *sq, size_t pos)
                {
                    this->sq = sq;
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

                const T &operator*() const
                {
                    if (this->sq == nullptr)
                        throw std::logic_error("Iterator uninitialized");

                    return (*(this->sq))[this->pos];
                }

                bool operator==(const const_iterator &that) const
                {
                    return this->sq == that.sq && this->pos == that.pos;
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
            return const_iterator(this, this->getSize()); // donc pas size-1 mais bien size
        }
};

// et maintenant la definition de l'op <<... on voit bien que ce n'est pas une fonction membre !
template <typename U, size_t SW>
std::ostream &operator<<(std::ostream &outgoing, const SimpQue<U, SW> &other)
{
    const Wagon<U, SW> *w = other.first; // on a le droit car on l'avait declaree amie

    while (w != nullptr)
    {
        outgoing << "Wagon: ";
        for (size_t i = 0; i < w->getSize(); i++)
            outgoing << w->get(i) << " "; // suppose la presence d'operator<< sur le type U
        outgoing << std::endl;
        w = w->getNext();
    }

    return outgoing; // sert a chainer (ex. cout << w1 << w2 << endl, et oui, le << s'evalue de gauche a droite donc cout << w1 retourne cout, et ainsi de suite)
}

#endif