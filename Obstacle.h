#include <GL/glut.h> 
#include <stdio.h>



class Obstacle{

    private:
        
        float xSpeed;
        bool moving;

    public:
        float x;
        float y;
        int width;
        int height;
        Obstacle(int,int);
        void show();
        void update();
        void move();
        void stop();

};