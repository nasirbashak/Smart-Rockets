#include<stdlib.h>
#include<GL/glut.h> 
#include<stdio.h>
#include "Population.h"
#include"PApplet.h"



int age;
int lifeSpan = 500;
int generations = 1;
int deadRockets = 0;
int populationSize =  20;
int winningRockets = 0;
Population population;

float obstacleWidth = 200;
float obstacleHeight = 25;
float obstacleX = (WIDTH/2)-(obstacleWidth/2);
float obstacleY = (HEIGHT/2)-(obstacleHeight/2);

int targetX = WIDTH/2;
int targetY = HEIGHT-50;
int targetSize = 50;

PVector target(500,550);

PVector stars[100];

int x = 100;
int y = 100;
int size = 15;

bool showNumber = false;

Obstacle rect(obstacleX,obstacleY);

float mapp(float value, float istart, float istop, float ostart, float ostop) {

    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));

}

void background(float r,float g,float b){
    float spaceR = mapp(r,0,255,0,1);
    float spaceG = mapp(g,0,255,0,1);
    float spaceB = mapp(b,0,255,0,1);

    glClearColor(spaceR,spaceG,spaceB,1.0);

}

void createSpace(){

    for(int i=0;i<100;i++){

        float x = rand()%WIDTH;
        float y = rand()%HEIGHT;
        float z = rand()%100;
        stars[i].add(PVector(x,y,z));

    }

}

void init(){

    //glClearColor(0.5,0.5,0.5,1.0);
    background(0,59,89);
    glColor3f(0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1000,0,600,100,-100);
    glMatrixMode(GL_MODELVIEW);

    lifeSpan = 500;
    target.add(500,550);
    population.init();
    createSpace();

    //PlaySound(TEXT("recycle.wav"), NULL, SND_FILENAME);
   // PlaySound("audio.mp4",NULL,SND_FILENAME);

}



void drawSpace(){

  
    float spaceR = mapp(255,0,255,0,1);
    float spaceG = mapp(255,0,255,0,1);
    float spaceB = mapp(255,0,255,0,1);

    glColor3f(spaceR,spaceG,spaceB);
    glPointSize((int)rand()%3);
    
        glBegin(GL_POINTS);
            for(int i=0;i<100;i++){
                glVertex3f(stars[i].x,stars[i].y,stars[i].z);
            }
        glEnd();
  





}


void renderBitmap(float x , float y, void *font, char *string){
    char *c;
    glRasterPos2f(x,y);
    for(int i = 0; c[i] != '\0'; i++){
	    glutBitmapCharacter(font, c[i]);
    }
}

void drawText(char *str,float x,float y){
    glColor3f(1.f,1.f,1.f);
    char buf[100] = {0};
    sprintf(buf,str);
    renderBitmap(x,y,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}


void drawTargetPlanet(){

    glPushMatrix();
        glTranslatef(WIDTH/2,HEIGHT-50,0);    
        glColor3f(0.0,1.0,0.0);
        glutSolidTorus(15,10,60,200);
    glPopMatrix();

}

void drawEarth(){
    
    GLfloat position[]={WIDTH/2,-HEIGHT/1.1,1.5,1.0};
    glPushMatrix();
        glTranslatef(WIDTH/2,-HEIGHT/1.1,0);
        glColor3f(0.0,0.0,0.1);
        glutSolidTorus(100,WIDTH/2,60,200);
    glPopMatrix();

}


void drawObstacle(){

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
        glVertex2f(obstacleX,obstacleY);
        glVertex2f(obstacleX,obstacleY-(obstacleHeight));
        glVertex2f(obstacleX+(obstacleWidth),obstacleY-(obstacleHeight));
        glVertex2f(obstacleX+(obstacleWidth),obstacleY);
    glEnd();

}

void drawTarget(){

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_QUADS);
        glVertex2f(targetX-targetSize/2,targetY);
        glVertex2f(targetX-targetSize/2,targetY-targetSize);
        glVertex2f(targetX+targetSize/2,targetY-targetSize);
        glVertex2f(targetX+targetSize/2,targetY);
    glEnd();

}

void text(int message,float x,float y, float z){
         
            glColor3f(1,1,1);
            char c[100];
            sprintf(c,"%d",message);
            glRasterPos2f(x, y);
            for(int i = 0; c[i] != '\0'; i++){
		        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
            }

}

void text(char *message,float x,float y, float z){

            glColor3f(1,1,1);
            char c[100];
            sprintf(c,"%s",message);
        
            glRasterPos2f(x, y);
           
            for(int i = 0; c[i] != '\0'; i++){
		        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
            }

}


void draw(){

    glClear(GL_COLOR_BUFFER_BIT);
    drawSpace();
    drawEarth();
    drawTargetPlanet();
    glLineWidth(1);
    // drawTarget();
    //drawObstacle();
    rect.show();
    rect.update();
    population.show();
    
    text("Generations : ",10,HEIGHT-25,10);
    text(generations,150,HEIGHT-25,10);

    text("Age : ",10,HEIGHT-50,10);
    text(age,75,HEIGHT-50,10);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();

}

void timer(int t){
       
    for(int i=0;i<1;i++){

        population.update(rect);
        age++;
       
        if(age >lifeSpan){
    
            printf("age reached %d\n",age);
            age=0;
            generations++;
           
            population.~Population();
            population.evaluate(PVector(500,550));
            population.selection();

        }
    }
    draw();
    glutTimerFunc(1000/60,timer,0);

}


void keys(unsigned char key , int x, int y)
{
    if(key == 'x'){
        exit(0);
    }

}

void myMenu(int option){
    switch(option){
        
        case 1:
                showNumber = true;
                break;
        case 2:
                showNumber = false;
                break;
        case 3:
                rect.move() ;
                break;
        case 4: 
                rect.stop() ;
                
                break;

    }

}

int main(int argc , char ** args){

    glutInit(&argc,args);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Smart Rockets");
    init();
    glutDisplayFunc(draw);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(keys);
    glutCreateMenu(myMenu);
    glutAddMenuEntry("RocketNumber On",1);
    glutAddMenuEntry("RocketNumber Off",2);
    glutAddMenuEntry("Move Obstacle",3);
    glutAddMenuEntry("Stop Obstacle",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

} 