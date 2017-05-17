#include "../Head/Cromossomo.h"
#include <stdlib.h>
#include <ctime>
#include <stdio.h>

// construtor princinal gera um cromossomo com genes aleatorios
Cromossomo :: Cromossomo ()
{
   gene = new int[MAXCROMGENE];                             // genes do cromossomo
   for (int i = 0; i < MAXCROMGENE; ++i)                    // gera um conjunto de gene randomico
   {
      gene[i] = rand() % (MAXRANDOM*2)+1 + MAXRANDOM;       //adiciona gene = random (-MAXRANDOM ; MAXRANDOM)
   }
   evaluation = 0;                                          // inicia o valor da avaliação
   probability = 0;                                         //inicia a probabilidade
}

//construtor2 gera cromossomo de acordo com os parametros
Cromossomo ::  Cromossomo(int* newGene, float newEvaluation, float newProbability)
{
   gene = newGene;
   evaluation = newEvaluation;
   probability = newProbability;
}


// COPY ==================================================

// Gera uma copia do cromossomo
Cromossomo* Cromossomo :: cloneCromossomo()
{
   int* cloneG = cloneGene();
   Cromossomo* cloneCromossomo = new Cromossomo (cloneG,evaluation,probability);
   return cloneCromossomo;
}

// gera uma copia do gene
int* Cromossomo :: cloneGene()
{
   int*  clone = new int [MAXCROMGENE];
   for (int i = 0; i < MAXCROMGENE; ++i)
   {
      clone[i] = gene[i];
   }
   return clone;
}

//PRINTS ===================================================

// exibe os parametros do cromossomo
void Cromossomo :: printCromossomo()
{
   if (gene != NULL)
   {
      for (int i = 0; i < MAXCROMGENE; ++i)
      {
         printf("\n Gene %d : %d ",i,gene[i]);
      }
   }
   printf("\n Evaluation : %d",evaluation);
   printf("\n probability : %lf \n",probability);
}

// GET SET====================================================

int    Cromossomo :: getEvaluation() { 
   return evaluation; }
int    Cromossomo :: getGene(int pos) { 
   return gene[pos]; }

double    Cromossomo :: getProbability() { 
   return probability; }

void Cromossomo :: setGene(int pos, int value) { gene[pos] = value;}
void Cromossomo :: setEvaluation(int value) { evaluation = value; }
void Cromossomo :: setProbability(double value) { probability = value; }

