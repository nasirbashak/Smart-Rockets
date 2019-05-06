#include"Population.h"
#include<stdio.h>
#include <time.h>       

Population :: Population(){

    

}
Population :: ~Population(){

  for(int i=0;i<populationSize;i++){
        rockets[i].~Rocket();
    }

         
    

}

void Population:: init(){
    populationSize = 20;

    
    

    for(int i=0;i<populationSize;i++){
        rockets[i].init();
    }


}


void Population ::show(){
    for(int i=0;i<populationSize;i++){
        rockets[i].show();
    }
}

void Population ::update(){
    for(int i=0;i<populationSize;i++){
        rockets[i].update();
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
    //for (Rocket rocket : rockets) {
      rockets[i].fitness /= maxfit;
     // printf("%d fitness= %f\n",(c++), rockets[i].fitness);

    }

    
    int index=0;
    matingPool = new Rocket[9000];

    //for (Rocket rocket : rockets) {
        for(int i=0;i<populationSize;i++){

      float n = rockets[i].fitness * 100;
     // printf("n = %f\n",n);
      
      for (int j = 0; j < n; j++) {
      //  matingPool[index++] 
        Rocket r = rockets[i];
        matingPool[(index++)].copy(r);

       /// printf("j = %d\n",j);
       // printf("%d matingpool = %f\n",index,matingPool[(index++)]);
        
      }
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
      newRockets[i].copy(Rocket(child));
    //  printf("i and popS %d,%d\n",i,populationSize);
      //printf("newRocket[%d] = %f,%f\n",i,newRockets[i].pos.x,newRockets[i].pos.y);
    }

   // delete []matingPool;

    for(int i=0;i<populationSize;i++){

    this->rockets[i].copy(newRockets[i]);
    //  printf("Rocket[%d] = %f,%f\n",i,rockets[i].pos.x,rockets[i].pos.y);
    }
  }




