package TP1;
import TP1.Pixel;

public class Image {
    private int hauteur;
    private int largeur;
    private Pixel tabPixel[][];

    public Image(int hauteur, int largeur){
        this.hauteur = hauteur;
        this.largeur = largeur;
        this.tabPixel = new Pixel[hauteur][largeur];
        for(int h = 0; h < hauteur; h++){
            for(int l = 0; l < largeur; l++){
                this.tabPixel[h][l] = new Pixel();
            }
        }
    }

    public Pixel getPixel(int hauteur, int largeur){
        return this.tabPixel[hauteur][largeur];
    }

    public void setPixel(int hauteur, int largeur, Pixel pixel){
        this.tabPixel[hauteur][largeur] = pixel;
    }

    public String toString(){
        String res = "";
        for(int h = 0; h < this.hauteur; h++){
            res+= "[";
            for(int l = 0; l < this.largeur; l++){
                res += this.tabPixel[h][l];
                if(l+1 != largeur) res+="|";
            }
            res+= "]\n";
        }
        return res;
    }

    public static void main(String args[]){
        Image i = new Image(10,10);
        System.out.println(i.toString());
    }
}