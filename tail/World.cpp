#include <stdlib.h>
#include "../head/World.h"
#include <math.h>

// gera a primeira geracao
World :: World ()
{
   generatePopulation();
   generateEvaluation();
}

// cria populacao de cromossomos aleatorios
void World :: generatePopulation()
{
   population = new Cromossomo*[TOTALPOPULATION];
   for (int i = 0; i < TOTALPOPULATION; i++)
   {
      population[i] = new Cromossomo();
   }
}

// avalia cada individuo da populacao
void World :: generateEvaluation()
{
   int* gene = new int[MAXCROMGENE];
   int evaluation;
   for (int i = 0; i < TOTALPOPULATION; i++)   // para cada individuo da populacao
   {
      gene = population[i] -> cloneGene();
      evaluation = 0;

       //resolve a funcao f(x) = sum 100*(x(i)^2 - x(i+1))^2 + (1 - x(i))^2;
       // adiciona a pontuacao obtida como metrica de avalicao ao cromossomo
      for (int j = 0; j < MAXCROMGENE; j++)
      {
         evaluation += (j+1) * gene[j];
      }
      evaluation = evaluation - 30;

      population[i] -> setEvaluation(abs(evaluation));
   }

   free(gene);
}

// gera probabilidade de cada individuo de acordo com a roleta
void World :: generateProbability()
{
   double *fitPerUnit   = new double[TOTALPOPULATION];
   double *probability = new double[TOTALPOPULATION];

   double fitTotal =  0;

    // fitness stage
   for (int i = 0; i < TOTALPOPULATION ; i++)
   {
      int evaluation = population[i] -> getEvaluation();

      double fit = 1.0f / (1+ evaluation);    //calcula o fitness
      fitPerUnit[i] =  fit;                   //fitness de cada individuo
      fitTotal += fitPerUnit[i];              //valor total fitness
   }

    //probability stage
   for (int j = 0; j < TOTALPOPULATION; j++)
   {
      double newValue;
      newValue = (double)(fitPerUnit[j] / fitTotal);
      probability[j]  = newValue;

   }

    // Roulette Wheel stage
   double prob = 0;
   for (int i = 0; i < TOTALPOPULATION; i++)
   {
      prob += probability[i];
      probability[i] = prob;
   }

   for (int i = 0; i < TOTALPOPULATION; i++)              //set probabilidade Acumulativa
   {
      population[i] -> setProbability (probability[i]);   // adciona ao cromosso a probabilidade acumulativa
   }

   free(fitPerUnit);
   free(probability);
}

//Seleciona a proxima geracao de inviduos
void World :: selectNextGeneration()
{
    // Random num 0-1 stage
   Cromossomo** newPopulation = new Cromossomo*[TOTALPOPULATION];
   for (int i = 0; i < TOTALPOPULATION; i++)
   {
      double randomValue = ((rand()  % 99) + 1.0)  / 100;

      int position = 0;
      bool search = true;
      while (search)
      {
      // seleciona individuo mais apto para a proxima geracao  senao somente copia os individios da geracao anterior
         if (randomValue > population[position] -> getProbability())
         {
            position = (position + 1) % TOTALPOPULATION;
         }
         else
         {
            newPopulation[i] = population[position] -> cloneCromossomo();
            search = false;
         }
      }
   }
   population = newPopulation; // troca para a nova populacao
}


//cruza os individuos da populacao atual
void World :: crossOver()
{
    //Random step
   int * randomValue = new int[TOTALPOPULATION];

   for (int i = 0; i < TOTALPOPULATION; i++)             //gera vetor randomico
   {
      randomValue[i] = rand() % 100;
   }

   for (int i = 0; i < (TOTALPOPULATION); i++)           // para cada cromossomo
   {
      if (randomValue[i] < CROSSOVER)                    // verifica se o random esta dentro da % de taxa de cruzamento
      {

         int j = (i+1) % TOTALPOPULATION;                // procurar de forma circular
         int randomGene = rand() % (MAXCROMGENE + 1);    // escolhe cromossomo a ser herdado
         bool search = true;

        // procura indivio  diferente que esteja dentro da % de crossOver para cruzamento
        //caso nao encontre cruza com ele mesmo mantendo o valor
         while (search)
         {
            if (randomValue[j] < CROSSOVER)
            {
               int value  =  population[j] -> getGene(randomGene);
               population[i] -> setGene(randomGene,value);
               search = false;
            }
            else
               j  = (j+1) % TOTALPOPULATION;
         }
      }
   }

   free(randomValue);
}

// faz mutacao em genes de alguns individuos da populacao
void World :: mutation()
{
   int cromoPos;
   int genePos;
   int totalPop = TOTALPOPULATION * MAXCROMGENE;
   int mutateGeneTotal = (int) (totalPop / MUTATION);

   for (int i = 0; i < mutateGeneTotal; i++)
   {
      int cromoPos = rand() % TOTALPOPULATION;
      int genePos = rand() % MAXCROMGENE;
      int newGene = rand() % MAXRANDOM;

      population[cromoPos] -> setGene(genePos, newGene);
   }
}

// verifica se e resultado correto
bool World ::  findResult()
{
   bool result = true;

   for (int i = 0; i < TOTALPOPULATION; i ++)
   {
      if (population[i] -> getEvaluation() == 0)
      {
         for (int j = 0; j < MAXCROMGENE;  j++)
         {
            printf("Gene %d :  %d \n",j, population[i] -> getGene(j));
         }
         return   false;
      }
   }
   return result;
}
