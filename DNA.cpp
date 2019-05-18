#include "DNA.h"
#include <math.h>
#include <algorithm>
#include <iterator>
using namespace std;


DNA::DNA(){

}

DNA::DNA(PVector newGenes[],int size){

  for(int i=0;i<size;i++){ 
    this->genes[i] = newGenes[i];
  }
  
}

DNA::~DNA(){

  //delete[] genes;

}

void DNA::init(){

    for (int i = 0; i < lifeSpan; i++) {
        PVector gene;
        gene = gene.random2D();
        // gene.x*=10;
        //gene.y*=10;
        gene.setMag(maxforce);    
        // printf("%d Genes = %f,%f\n",i,gene.x,gene.y);    
      genes[i] = gene;
    }

}

float random(int n){
 
    return rand() % n;
 
}

void DNA :: mutation() {
 
    for (int i = 0; i < lifeSpan; i++) {
      if (random(1) < 0.01) {
        PVector gene;
        gene = gene.random2D();
        gene.setMag(0.1);        
        genes[i] = gene;
      }
    }
  
}

DNA DNA ::crossover(DNA partner) {

    PVector newgenes[lifeSpan];

    int mid = (int) random(lifeSpan);
    //printf("mid = %d\n",mid);

    for (int i = 0; i < lifeSpan; i++) {
      if (i > mid) {
        newgenes[i] = this->genes[i];
      } else {
        newgenes[i] = partner.genes[i];
      }
    }
    DNA d = DNA(newgenes,lifeSpan);

   return d;

}
