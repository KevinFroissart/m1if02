public class Pixel {
    private int un;
    private int deux;
    private int trois;

    public Pixel(){
        this.un = 0;
        this.deux = 0;
        this.trois = 0;
    }

    public int getUn(){
        return this.un;
    }

    public int getDeux(){
        return this.deux;
    }

    public int getTrois(){
        return this.trois;
    }

    public void setUn(int un){
        this.un = un;
    }

    public void setDeux(int deux){
        this.deux = deux;
    }

    public void setTrois(int trois){
        this.trois = trois;
    }

    @Override
    public String toString(){
        return this.un + "." + this.deux + "." + this.trois;
    }
}