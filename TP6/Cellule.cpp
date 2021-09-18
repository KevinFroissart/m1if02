#include <iostream>

template<typename T>
class Cellule
{
public:
    Cellule() : data(new T()), next(nullptr) {}
    Cellule(T data, Cellule *next) : data(data), next(next) {}
    T data;
    Cellule<T> *next;
private:
};

template<typename T>
class Liste
{
public:
    Liste()
    {
        head = nullptr;
        tail = head;
        taille = 0;
    }

    Liste(const Liste<T> &l)
    {
        head = l.head;
        tail = l.tail;
        taille = l.taille;
    }

    Liste(const Liste<T> &&l)
    {
        head = std::move(l.head);
        tail = std::move(l.tail);
        taille = std::move(l.taille);
    }

    Liste<T> &operator=(const Liste &autre)
    {
        taille = 0;
        head = nullptr;
        Cellule<T> *tmp = autre.head;
        while(tmp->next != nullptr)
        {
            addHead(tmp->data);
            tmp = tmp->next;
        }
        addTail(tmp->data);
        return *this;
    }

    void addHead(T data)
    {
        head = new Cellule<T>(data, head);
        if(taille == 0) tail = head;
        ++taille;
    }
    void addTail(T data)
    {
        tail->next = new Cellule<T>(data, nullptr);
        tail = tail->next;
        ++taille;
    }
    void afficher() const
    {
        std::string affichage = "";
        Cellule<T> *tmp = head;
        affichage += "[ ";
        for (int i = 0; i < taille; i++)
        {
            affichage += std::to_string(tmp->data) + " ";
            tmp = tmp->next;
        }
        affichage += "]";
        std::cout << affichage << std::endl;
    }

    virtual ~Liste()
    {
        while(head->next!=nullptr)
        {
            Cellule<T> *tmp = head;
            head = tmp->next;
            tmp->next = nullptr;
            --taille;
            delete tmp;
        }
        delete tail;
    }

private:
    Cellule<T> *head;
    Cellule<T> *tail;
    int taille;
};

int main()
{
    Liste<int> l;
    l.addHead(1);
    l.addHead(2);
    l.afficher();
    return 0;
}