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
class List
{
public:
    List()
    {
        head = nullptr;
        tail = head;
        taille = 0;
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

private:
    Cellule<T> *head;
    Cellule<T> *tail;
    int taille;
};

int main()
{
    List<int> l;
    l.addHead(1);
    l.addHead(2);
    l.afficher();
    return 0;
}