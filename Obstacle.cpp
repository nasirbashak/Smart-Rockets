#include"Obstacle.h"

int WIDTH = 1000;
int HEIGHT = 600;

Obstacle :: Obstacle(int x,int y){
    this->x=x;
    this->y=y;
    this->xSpeed = 2;
    width = 200;
    height = 25;
    moving = false;
}

float mappp(float value, float istart, float istop, float ostart, float ostop) {

    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));

}


void Obstacle:: show(){

    float bodyR = mappp(255,0,255,0,1);
    float bodyG = mappp(179,0,255,0,1);
    float bodyB = mappp(0,0,255,0,1); 
    glColor3f(bodyR,bodyG,bodyB);

    glBegin(GL_QUADS);
        glVertex2f(this->x                ,     this->y);
        glVertex2f(this->x                ,    this->y-(this->height));
        glVertex2f(this->x+(this->width)  ,   this->y-(this->height));
        glVertex2f(this->x+(this->width)  ,   this->y);
    glEnd();

}

void Obstacle ::update(){
    if(moving){

        this->x += xSpeed;

        if(this->x+(this->width) >= WIDTH || this->x <=0){
            xSpeed*=-1;
        }

    }
}

void Obstacle :: move(){
    this->moving = true;
    update();
}

void Obstacle :: stop(){
    this->moving = false;
    update();
}
