
#include "../tail/World.cpp"

int main ()
{
   srand((unsigned)time(0));                                 // para gerar numeros aleatorios reais. <- mudar isso
   World *world = new World();                               // cria mundo e sua primeira geracao com suas avaliacoes;
   static int generation = 0;                                // geracões passadas
   static bool search = true;                                // procurar resultado

   printf("\n\nSearching Result ... \n\n");


   while(search)                                             // enquanto nao encontrar o resultado
   {
      world -> generateProbability();                        // gera a probabilidade dos membros da populacao
      world -> selectNextGeneration();                       //seleciona proxima geracao
      world -> crossOver();                                  //faz cruzamento entre cromossomos
      world -> mutation();                                   //faz mutacoes de genes na populacao
      world -> generateEvaluation();                         // gera a avaliacao dos membros da populacao
      search =  world -> findResult();                       //proucura pelo cromossomo que resolva a funcao caso encontre
      generation++;
   }
   printf("\nGeneration : %d \n\n", generation);

   return 0;
}
