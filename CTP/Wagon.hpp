#ifndef __WAGON_HPP__
#define __WAGON_HPP__

#include <stdexcept>

template <typename T, size_t Capacity>
class Wagon
{
    private:
        // L'intérêt des paramètres templaest l'évaluatio a la compilation
        // On peut donc se passer d'allocation dynamique
        T array[Capacity];

        size_t size;
        Wagon *next;

    public:
        Wagon() : size(0), next(nullptr)
        {
        }

        // Piège  a la copie d'un Wagon il ne faut PAS recuperer son pointeur de suivant
        // Cloner un noeud ne signifie pas l'associer le clone a la liste existante, mais bel et bien
        // le cloner de facon isolee
        Wagon(const Wagon &that) : size(that.size), next(nullptr)
        {
            // Suppose que la contiguité dans le tableau est assree en cas de suppression
            // Suppose aussi que le constructeur de copie de T est correctement fait
            for (size_t i = 0; i < this->size; i++)
                this->array[i] = that.array[i];
        }

        // Toujours déclarer lesdestructeurs virtuels car on ne sait pas qui pourra
        // etendre notre classe dans le futur et eventuellement rajouter des attributs
        // alloues dynamiquement.
        virtual ~Wagon()
        {
            // cette recursivite suppose que tout Wagon cree est alloue dynamiquement
            if (this->next != nullptr)
                delete next;
        }

        Wagon &operator=(const Wagon *that)
        {
            this->size = that.size;
            this->next = nullptr; // Pareil que pour la copie
            
            for (size_t i = 0; i < this->size; i++)
                this->array[i] = that.array[i];
            // S'il restait des elements a la fin du tableau ce n'est pas grave
            // car le size est bien copie et on fera attention lors de nos acces a ne pas
            // aller au dela

            return *this; // sert a chainer (ex. a = b = c;)
        }

        size_t getSize() const
        {
            return this->size;
        }

        bool isFull() const
        {
            return this->size == Capacity;
        }

        T &get(size_t index)
        {
            if (index >= this->size)
                throw std::overflow_error("Out of bounds");

            return this->array[index];
        }

        const T &get(size_t index) const
        {
            if (index >= this->size)
                throw std::overflow_error("Out of bounds");

            return this->array[index];
        }

        Wagon &add(const T &elem)
        {
            if (this->size == Capacity)
                throw std::overflow_error("Container is full");

            // Encore une fois suppose que le constructeur par copie de T est correctement fait
            this->array[size] = elem;
            size++;

            return *this; // sert a chainer (ex. a.add(3).add(5).add(-8);)
        }

        Wagon &setNext(Wagon *next)
        {
            this->next = next;

            return *this; // sert a chainer (ex. w.add(8).setNext(w2);)
        }

        Wagon *getNext() const
        {
            return this->next;
        }
};

#endif