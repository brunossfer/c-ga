#include "Config.h"

class Cromossomo{

private:

   int* gene;                   // conjunto de genes
   int evaluation;              // avalicao
   double probability;          // probabilidade de ocorrencia

public:
   Cromossomo();
   Cromossomo(int* newGene, float newEvaluation, float newProbability);

   Cromossomo* cloneCromossomo();

   int* cloneGene();

   int getEvaluation();
   int getGene(int);

   double getProbability();

   void printCromossomo();
   void setEvaluation(int);
   void setProbability(double);
   void setGene(int,int);

   ~Cromossomo();
};