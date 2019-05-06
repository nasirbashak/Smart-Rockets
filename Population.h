#include"Rocket.h"

//explicit int targetX ;
//explicit int targetY ;


class Population{
    private:
        int populationSize;
        Rocket rockets[20];
        Rocket *matingPool;
    public:

        Population();
        ~Population();
        void init();
        void show();
        void update();
        float evaluate(PVector target);
        void selection();


};