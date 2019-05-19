class PVector{

    private:

    
    public:
        float x;
        float y;
        float z;

        PVector(float x,float y,float z);
        PVector(float x,float y);
        PVector();
        PVector add(PVector v);
        PVector add(float x,float y);
        PVector copy();
        PVector mult(float n);
        float magSq();
        PVector div(float n);
        PVector normalize();
        float mag();
        PVector limit(float n);
        float heading();
        PVector setMag(float n);
        PVector fromAngle(float angle );
        PVector set(float x , float y);
        PVector set(float x , float y , float z);
        PVector set(PVector v);
        PVector random2D();



};