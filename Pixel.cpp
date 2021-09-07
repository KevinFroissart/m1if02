#include <iostream>
#include <vector>


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
    void print();
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

void Pixel::print(){
    std::cout << this->un << "." << this->deux << "." << this->trois;
}

class Image
{
public :
    Image(int hauteur, int largeur){
        this->tabPixel.resize(hauteur);
        for(int h = 0; h < hauteur; h++){
            this->tabPixel[h].resize(largeur);
            for(int l = 0; l < largeur; l++){
                this->tabPixel[h][l] = new Pixel();
            }
        }
        this->hauteur = hauteur;
        this->largeur = largeur;
    }
    void setPixel(int, int, Pixel*);
    Pixel* getPixel(int, int);
    void print();
private:
    int hauteur;
    int largeur;
    std::vector<std::vector<Pixel*> > tabPixel;
};

void Image::setPixel(int hauteur, int largeur, Pixel* pixel) {
    this->tabPixel[hauteur][largeur] = pixel;
}

Pixel* Image::getPixel(int hauteur, int largeur){
    return this->tabPixel[hauteur][largeur];
}

void Image::print(){
    for(int h = 0; h < this->hauteur; h++){
        std::cout << "[";
        for(int l = 0; l < this->largeur; l++){
            this->getPixel(h,l)->print();
            if(l+1 != largeur) std::cout << "|";
        }
        std::cout << "]" << std::endl;
    }
}

int main(){
    Image* i = new Image(10,10);
    i->print();
    return 0;
}