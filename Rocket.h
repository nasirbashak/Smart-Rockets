//#include "PVector.h"
#include<math.h>
#include "DNA.h"






class Rocket{


private:
    int x;
    int y;
    int ySpeed;
    int xSpeed;
    int size;
    bool completed;
    bool crashed;
  
    

     
     PVector vel;
     PVector acc;


     
     



public:
    float fitness;
    PVector pos;
    DNA Dna;
    Rocket();
    Rocket(DNA d);
    Rocket(const Rocket &cpy);
    ~Rocket();
    void init();
    void applyForce(PVector f);
    void init(int x, int y,int ySpeed);
    void show();
    void update();
    void drawPath(PVector);
    Rocket copy(Rocket r);
    float calcFittness(PVector target);
    





};