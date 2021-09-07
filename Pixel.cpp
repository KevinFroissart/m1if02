#include <iostream>

class Pixel
{
public :
    Pixel() : un(0), deux(0), trois(0){}
    int getUn();
    int getDeux();
    int getTrois();
    void setUn(int);
    void setDeux(int);
    void setTrois(int);
private:
int un;
int deux;
int trois;
};

int Pixel::getUn(){
    return this->un;
}

int Pixel::getDeux(){
    return this->deux;
}

int Pixel::getTrois(){
    return this->trois;
}

void Pixel::setUn(int un){
    this->un = un;
}

void Pixel::setDeux(int deux){
    this->deux = deux;
}

void Pixel::setTrois(int trois){
    this->trois = trois;
}

class Image
{
public :
    Image(int hauteur,const int largeur){
        pixel = new int[hauteur][largeur];
    }
private:
int hauteur;
int largeur;
int **pixel;
};