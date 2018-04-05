#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "tad.h"

int main(int argc, char const *argv[]) {
  // Inicializa variaveis do programa
  TipoFlags Flag;
  struct timeval beginT, endT;
  unsigned long time1 = 0;
  int ret, s, g;

  Flag.Passos = 0;
  Flag.Tempo = 0;

  Grafo G;
  G = LeituraDeEntrada(&Flag, &s, &g);

  // Processa dados obtidos no procedimento anterior
  // Obtem tempo de computacao
  gettimeofday(&beginT, NULL);
  ret = bfs(G, s, g);
  gettimeofday(&endT, NULL);

  // Imprime resultados solicitados pelo usuario de acordo com as flags obtidas previamente
  if(Flag.Passos){
      printf("%d\n", ret);
  }
  if(Flag.Tempo){
    time1 = ((endT.tv_sec * 1000000 + endT.tv_usec) - (beginT.tv_sec * 1000000 + beginT.tv_usec));
    printf("%ld\n",time1);   // Tempo de computacao
  }

  // Libera memoria utilizada no programa
  freeG(G);
    
  return 0;                 // Fim de programa
}
