#include<math.h>
#include "DNA.h"
#include "Obstacle.h"

class Rocket{

    private:
        int x;
        int y;
        int ySpeed;
        int xSpeed;
        int size;
        bool completed; 
        int number;     
        PVector vel;
        PVector acc;

    public:
        float fitness;
        bool crashed;
        PVector pos;
        DNA Dna;
        Rocket();
        Rocket(DNA d);
        Rocket(const Rocket &cpy);
        ~Rocket();
        void init();
        void applyForce(PVector f);
        void init(int x, int y,int ySpeed);
        void show(int);
        void update(Obstacle);
        void drawPath(PVector);
        Rocket copy(Rocket r);
        float calcFittness(PVector target);
    
};