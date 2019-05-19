#include "PVector.h"
extern int age;
extern int lifeSpan;

class DNA{

    private:
    
        float maxforce = 0.5;

        
    public:
     
        PVector genes[500];
        DNA();
        DNA(PVector p[],int n);
        ~DNA();
        void init();
        void mutation();
        DNA crossover(DNA d);

};