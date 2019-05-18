#include"Rocket.h"


class Population{
    private:
        int populationSize;
        Rocket rockets[20];
        Rocket *matingPool;
    public:
        int deadRockets;
        Population();
        ~Population();
        void init();
        void show();
        void update(Obstacle);
        float evaluate(PVector target);
        void selection();


};