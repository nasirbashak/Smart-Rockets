
#include<stdlib.h>
#include<GL/glut.h> 
#include<stdio.h>
#include "Population.h"
#include"PApplet.h"

int age;
int lifeSpan = 500;
Population population;

float obstacleWidth = 200;
float obstacleHeight = 25;
float obstacleX = (WIDTH/2)-(obstacleWidth/2);
float obstacleY = (HEIGHT/2)-(obstacleHeight/2);

int targetX = WIDTH/2;
int targetY = HEIGHT-50;
int targetSize = 50;

PVector target(500,550);

int x = 100;
int y = 100;
int size = 50;



void init(){

    glClearColor(0.5,0.5,0.5,1.0);

    glColor3f(0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1000,0,600,100,-100);
    glMatrixMode(GL_MODELVIEW);

    lifeSpan = 500;
    target.add(500,550);
    population.init();

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

void draw(){

    glClear(GL_COLOR_BUFFER_BIT);

    drawEarth();
    drawTargetPlanet();
    glLineWidth(1);
    // drawTarget();
    drawObstacle();
    population.show();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();

}

void timer(int t){
       
    for(int i=0;i<1;i++){

        population.update();
        age++;
        if(age >lifeSpan){
    
            printf("age reached %d\n",age);
            age=0;
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

    glutMainLoop();

}