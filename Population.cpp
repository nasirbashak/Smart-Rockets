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
      
      //  printf("updated rocket[%d] = %f,%f\n",i,rockets[i].pos.x,rockets[i].pos.x);
    }

}

float Population :: evaluate(PVector target){
    float avgfit = 0;
    float maxfit = 0;
    //  printf("target in evaluate%d,%d\n",0,0);//targetX,targetY);
    for(int i=0;i<populationSize;i++){
      float f =  rockets[i].calcFittness(target);
        //printf("%d fitness= %f\n",i,rockets[i].fitness);
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
      if(f!=(float)1){
        continue;
      }

      printf("%d Original rocket fitness = %f\n",i,f);
      // printf("n = %f\n",n);
      
      for (int j = 0; j < n; j++) {
        //  matingPool[index++] 
        Rocket r = Rocket(rockets[i]);
        //r = r.copy(rockets[i]);
        //matingPool[(index++)].copy(r);
        //matingPool[(index++)] = Rocket(r);
        matingPool[(index++)] = Rocket(rockets[i]);
        // printf("j = %d\n",j);
        // printf("%d Selected rocket fitness = %f\n",j,r.fitness);
        Rocket r2 = Rocket(matingPool[index]);
        float f = r2.pos.x;
       //  printf("%d matingpool pos.x = %f\n",index,f);
        
      }
    }

    for(int i=0;i<index ;i++){

        Rocket r1 = Rocket(matingPool[i]);
        Rocket r2 = matingPool[i];

        // printf("%d Rocket pos in constructor = %f,%f\n",i,r1.pos.x,r1.pos.y);
        // printf("%d Rocket pos without constructor = %f,%f\n",i,r2.pos.x,r2.pos.y);

        // printf("%d Rocket fitness in constructor = %f\n",i,r1.fitness);
        // printf("%d Rocket fitness without constructor = %f\n",i,r2.fitness);

    }

    //printf("avgfit return val = %f\n",avgfit);
    //printf("maxFit = %fn",maxfit);

    return avgfit;

}

Rocket randomDNA(Rocket rockets[],int populationSize){

    srand(time(0));
    int r = rand()%populationSize;
    int i = r* populationSize;
   // printf("rand() = %d and index = %d and populationsize = %d\n",r,i,populationSize);
    Rocket rocket = rockets[r];
   // printf("random rocket = %f,%f\n",rocket.pos.x,rocket.pos.y);

    return rocket;

}

void Population ::selection() {

    Rocket newRockets[200];
    //  printf("selection\n");

    for (int i = 0; i < populationSize; i++) {

      DNA parentA = randomDNA(matingPool,populationSize).Dna;
      DNA parentB = randomDNA(matingPool,populationSize).Dna;
      DNA child = parentA.crossover(parentB);
     // printf("%d child dna = %f,%f\n",i,child.genes[i].x,child.genes[i].y);
      child.mutation();
      //newRockets[i].copy(Rocket(child));
      newRockets[i] = Rocket(child);

    //  printf("i and popS %d,%d\n",i,populationSize);
      //printf("newRocket[%d] = %f,%f\n",i,newRockets[i].pos.x,newRockets[i].pos.y);
    }

    //delete []matingPool;

    for(int i=0;i<populationSize;i++){

      this->rockets[i].copy(newRockets[i]);
      //this->rockets[i] = Rocket(newRockets[i]);

        //for(PVector p : rockets[i].Dna.genes ){
            // printf("%d Rocket genes = %f,%f\t",i,p.x,p.y);
          //}
      //  printf("\n");
      //printf("Rocket[%d] = %f,%f\n",i,rockets[i].Dna.genes[0].x,rockets[i].Dna.genes[0].y);
    }

  }