#include "Rocket.h"
#include <GL/glut.h> 

#include <stdio.h>
#include <math.h>
#include "PApplet.h"
#define PI 3.1412

extern float obstacleWidth ;
extern float obstacleHeight ;
extern float obstacleX ;
extern float obstacleY ;




 Rocket :: Rocket(){
     DNA Dna;
        
}
Rocket :: Rocket(DNA d){

    pos = PVector(1000 / 2, 20);
    vel = PVector(0,0);
    vel = vel.random2D();
    //printf("velocity1 = %d,%d\n",vel.x,vel.y);
    vel.setMag(0.2);
    acc = PVector(0, 0);
    size= 10;



     this->Dna= d;
        
}

Rocket :: Rocket(const Rocket &cpy){
      this->pos = cpy.pos;
    this->vel = cpy.vel;
    this->acc = cpy.acc;
    this->size = cpy.size;
    this->fitness = cpy.fitness;
    
     this->Dna = cpy.Dna;
        
}


Rocket :: ~Rocket(){
    completed = false;
    crashed = false;
    Dna.~DNA();
}

Rocket Rocket:: copy(Rocket r){
    //this->pos = r.pos;
    //this->vel = r.vel;
    //this->acc = r.acc;
    //this->size = r.size;
    this->pos = PVector(1000 / 2, 20);
    this->vel = PVector(0,0);
    this->vel = vel.random2D();
    this->fitness = r.fitness;
    //printf("velocity1 = %d,%d\n",vel.x,vel.y);
    this->vel.setMag(0.2);
    this->acc = PVector(0, 0);
    this->size= 10;
    this->Dna = r.Dna;
}


void Rocket :: init(){
    pos = PVector(1000 / 2, 20);
    vel = PVector(0,0);
    vel = vel.random2D();
    //printf("velocity1 = %d,%d\n",vel.x,vel.y);
    vel.setMag(0.2);
    acc = PVector(0, 0);
    size= 10;
    completed = false;
    Dna.init();

   // printf("velocity2 = %f,%f\n",vel.x,vel.y);



}




void Rocket :: applyForce(PVector force){
    acc.add(force);
}


float sq(float n) {
    return n*n;
  }

float dist(float x1, float y1, float x2, float y2) {
    return sqrt(sq(x2-x1) + sq(y2-y1)); 
  }

  float map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
  }

void Rocket :: drawPath(PVector p){


  glColor3f(0.0,1.0,0.0);
  glPointSize(50);
  glBegin(GL_POINTS);
    glVertex2f(p.x,p.y);
    glVertex2f(p.x+10,p.y+10);
    printf("pos = %f,%f\n",p.x,p.y);
  glEnd();



}


void Rocket :: update(){

  //printf("Obstacle Width = %f\n",obstacleWidth);

    applyForce(Dna.genes[age]);
    

  float d = dist(this->pos.x,this->pos.y,500,550);
  if(d<50){
    this->completed = true;
    this->pos.x = 500;
    this->pos.y = 550;
  }

  if(this->pos.x<0 || this->pos.x >WIDTH- this->size || this->pos.y <0 || this->pos.y > HEIGHT){
    this->crashed = true;

  }

  if( this->pos.x>=obstacleX && this->pos.x<= obstacleX+obstacleWidth &&  this->pos.y>=obstacleY-obstacleHeight && this->pos.y<=obstacleY){
    this->crashed = true;
  }






    if(!completed && !crashed){
      vel.add(acc);
      pos.add(vel);
      acc.mult(0);
     

    }

    
}




void Rocket :: init(int x,int y,int ySpeed){
    this->x = rand()%100;//random(1000);//
    this->y = 0;
    this->ySpeed = rand()%5;//random(5);//
    this->xSpeed = rand()%5;//random(5);//
    this->size=15;


}


void Rocket :: show(int number){

   //  printf("position = %d ,%d \n",pos.x,pos.y);

    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(vel.heading()*10,1,1,1);
   
    //printf("head = %f\n",vel.heading());
     
    
      


     //nose section

      float noseR = map(165,0,255,0,1);
      float noseG = map(42,0,255,0,1);
      float noseB = map(42,0,255,0,1);  


     //fill(165, 42, 42);
    //glColor3f(1.0,0.5,1.0);
    glColor3f(noseR,noseG,noseB);

    glBegin(GL_TRIANGLES);
        glVertex2f(0+size/2,0+size/1.5);
        glVertex2f(0+size/2-size/1.5,0);
        glVertex2f(0+size/2+size/1.5,0);

    glEnd();

    //body section
    

         if (completed) {
      //fill(50, 205, 50);

      float bodyR = map(50,0,255,0,1);
      float bodyG = map(205,0,255,0,1);
      float bodyB = map(50,0,255,0,1);  
       glColor3f(bodyR,bodyG,bodyB);

    } else if (crashed) {
      //fill(128, 128, 128);

      float bodyR = map(50,0,255,0,1);
      float bodyG = map(50,0,255,0,1);
      float bodyB = map(50,0,255,0,1); 

       glColor3f(bodyR,bodyG,bodyB);

    } else {
      //fill(255, 150);

       float bodyR = map(255,0,255,0,1);
      float bodyG = map(255,0,255,0,1);
      float bodyB = map(255,0,255,0,1);
      float bodyA = map(150,0,255,0,1); 

       glColor3f(bodyR,bodyG,bodyB);
      // glClearColor(bodyR,bodyG,bodyB,bodyA);
    }



    //glColor3f(0.0,0.0,1.0);
   
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(0,0-2*size);
        glVertex2f(0+(size),0-2*size);
        glVertex2f(0+(size),0);
    glEnd();

    if (!completed && !crashed) {

      glPushMatrix();
      glTranslatef(0,-4*size,0);
       glRotatef(180,1,0,0);

      //fill(255, 140 + random(0, 115), random(0, 128));

          int tempGreen = 140+rand()%115;
          int tempBlue = rand()%128; 
      
        float thrustR = map(255,0,255,0,1);
        float thrustG = map(tempGreen,0,255,0,1);
        float thrustB = map(tempBlue,0,255,0,1);      


      // draw thrust flame
        //glColor3f(0.5,0.0,0.0);
         glColor3f(thrustR,thrustG,thrustB);
      
      glBegin(GL_TRIANGLE_STRIP);
         // glVertex2f(-14, -3);
         // glVertex2f(-35, 0);
         // glVertex2f(-14, 3);
        glVertex2f(0,-2*size);
        glVertex2f(0+size/2,-2*size);
        glVertex2f(0+size/4,-size/2);

      
      glEnd();

      glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0+size/2,-2*size);
        glVertex2f(0+size,-2*size);
        glVertex2f(0+3*size/4,-size/2);
     
      glEnd();
      glPopMatrix();
    }

    // displing rocket number
     glColor3f(1,0,0);
          char c[10];
     sprintf(c,"%d",number);

     glRasterPos3f(0, -1.5*size, 0);
	  for(int i = 0; c[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);




     glPopMatrix();

}





float Rocket :: calcFittness(PVector target){

    //printf("position = %d ,%d \ntarget = %d %d\n",pos.x,pos.y,target.x,target.y);

    float d = dist(this->pos.x,this->pos.y,WIDTH/2,(HEIGHT-50));
    fitness = map(d, 0, WIDTH, WIDTH, 0);
    //printf("in Rocket WIDTH = %d and HEIGHT = %d\n",WIDTH,HEIGHT);
    
    if (completed) {
      fitness *= 10;
    } else if (crashed) {
      fitness /= 10;
    }
    //printf("\nvelocity in calcF = %f,%f\n",vel.x,vel.y);

     printf("d and fitness %f , %f\n",d,fitness);

    return fitness;
}









