#ifndef CIRCULAIRE_HPP
#define CIRCULAIRE_HPP
#define DEFAULT_CAPACITY 10

template <typename T>
class Circulaire {
private:
    size_t taille;
    size_t capacite;
    T *data;

    void expend() {
        T *new_data = new T[capacite + DEFAULT_CAPACITY];
        for(size_t i = 0; i < capacite; i++) {
            new_data[i] = data[i];
        }
        this->capacite += DEFAULT_CAPACITY;
        delete[] data;
        data = new_data;
    }
public:
    Circulaire() : taille(0), capacite(DEFAULT_CAPACITY), data(nullptr) {
        std::cout << "Circulaire()" << std::endl;
    }
    Circulaire(size_t taille, const T &data) : taille(taille), capacite(DEFAULT_CAPACITY) {
        std::cout << "Circulaire(size_t taille, const T &data)" << std::endl;
        this->data = new T[taille];
        for(size_t i = 0; i < taille; i++)
            this->data[i] = data;
    }
    Circulaire(const Circulaire &that) {
        std::cout << "Circulaire(const Circulaire &that)" << std::endl;
        *this = that;
    }
    Circulaire(Circulaire &&that) {
        std::cout << "Circulaire(Circulaire &&that)" << std::endl;
        *this = std::move(that);
    }
    virtual ~Circulaire() {
        std::cout << "~Circulaire()" << std::endl;
        delete[] data;
    }
    bool operator==(const Circulaire<T> &that) {
        return this->capacite == that.capacite && this->taille == that.taille && this->data == that.data;
    }
    bool operator!=(const Circulaire<T> &that) {
        return !(*this == that);
    }
    Circulaire &operator=(const Circulaire &that) {
        std::cout << "Circulaire &operator=(const Circulaire &that)" << std::endl;
        if(*this != that) {
            this->data = nullptr;
            delete[] data;
            this->taille = that.taille;
            this->capacite = that.capacite;
            this->data = new T[that.taille];
            std::cout << this->capacite << " " << this->taille << std::endl;
            for(size_t i = 0; i < that.taille; i++)
                this->data[i] = that.data[i];
        }
        return *this;
    }
    Circulaire &operator=(Circulaire &&that) {
        std::cout << "Circulaire &operator=(Circulaire &&that)" << std::endl;
        this->taille = std::move(that.taille);
        this->capacite = std::move(that.capacite);
        this->data = std::move(that.data);
        that.data = nullptr;
        return *this;
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const Circulaire<U> &that);

    std::ostream &print(std::ostream &out, size_t pos) const {
        if(pos < this->taille) {
            out << this->data[pos] << " ";
            print(out, ++pos);
        }
        return out;
    }

    void insere(size_t pos, const T &data) {
        if(pos > this->taille) this->taille++;
        if(this->taille >= this->capacite) expend();
        this->data[pos] = data;
    }

    const T &operator[](int pos) const {
        return const_cast<const T &>(this->data[pos]);
    }

    T &operator[](int pos) {
        return this->data[pos];
    }

    int search(const T &data) {
        for(size_t i = 0; i < this->taille; i++)
            if(this->data[i] == data) return i;
        return -1;
    }
};

#endif