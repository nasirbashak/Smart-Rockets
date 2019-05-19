#include"Population.h"
#include<stdio.h>
#include <time.h> 


Population :: Population(){

}

Population :: ~Population(){

  deadRockets = 0;
  for(int i=0;i<populationSize;i++){
        rockets[i].~Rocket();
    }

}

void Population:: init(){
 
    populationSize = 20;
    deadRockets = 0;

    for(int i=0;i<populationSize;i++){
        rockets[i].init();
    }

}

void Population ::show(){
  
    for(int i=0;i<populationSize;i++){
        rockets[i].show(i);
    }

}

void Population ::update(Obstacle rect){
   
    for(int i=0;i<populationSize;i++){
        rockets[i].update(rect);
      
    }

}

float Population :: evaluate(PVector target){
    float avgfit = 0;
    float maxfit = 0;
    for(int i=0;i<populationSize;i++){
      float f =  rockets[i].calcFittness(target);
       
        if (rockets[i].fitness > maxfit) {
        maxfit = rockets[i].fitness;
      }
      avgfit += rockets[i].fitness;
    }

    avgfit /= populationSize;
    printf("maxfit and avgfit = %f,%f\n",maxfit,avgfit);

    int c=0;
    for(int i=0;i<populationSize;i++){
      rockets[i].fitness /= maxfit;
    }

    
    int index=0;
    matingPool = new Rocket[9000];

    for(int i=0;i<populationSize;i++){

      int n = rockets[i].fitness * 100;
      float f = rockets[i].fitness;
      if(f>=(float)0.7){
      
      

     // printf("%d Original rocket fitness = %f\n",i,f);
  
      
      for (int j = 0; j < n; j++) {
       
        Rocket r = Rocket(rockets[i]);
       
        matingPool[(index++)] = Rocket(rockets[i]);
     
        Rocket r2 = Rocket(matingPool[index]);
        float f = r2.pos.x;
       
        
      }


    }else{
      printf("Skipped %d\n",i);
    }
    }

    for(int i=0;i<index ;i++){

        Rocket r1 = Rocket(matingPool[i]);
        Rocket r2 = matingPool[i];

    }

    return avgfit;

}

Rocket randomDNA(Rocket rockets[],int populationSize){

    srand(time(0));
    int r = rand()%populationSize;
    int i = r* populationSize;
    Rocket rocket = rockets[r];

    return rocket;

}

void Population ::selection() {

    Rocket newRockets[200];

    for (int i = 0; i < populationSize; i++) {

      DNA parentA = randomDNA(matingPool,populationSize).Dna;
      DNA parentB = randomDNA(matingPool,populationSize).Dna;
      DNA child = parentA.crossover(parentB);
      child.mutation();
      newRockets[i] = Rocket(child);
    }


    for(int i=0;i<populationSize;i++){

      this->rockets[i].copy(newRockets[i]);
      
    }

  }