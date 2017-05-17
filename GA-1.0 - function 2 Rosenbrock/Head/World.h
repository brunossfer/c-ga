#include  "../Tail/Cromossomo.cpp"
#include  "Config.h"

class World
{
        private:
   Cromossomo** population;      // populacao de cromossomos

        public:
   World();
   void generatePopulation();    // gera a populacao inicial de cromossomos
   void generateEvaluation();    // gera a avaliacao de cada individuo
   void generateProbability();   // gera a probabilidade de sobrevivencia do cromossomo
   void selectNextGeneration();  // seleciona a proxima geracao de cromossomos
   void crossOver();             // cruza cromossomos selecionados para a proxima geracao
   void mutation();              // faz mutacoes nos individuos gerados
   bool findResult();            // encontra o melhor resultado

   ~World();

};
