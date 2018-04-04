#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "TAD.h"

int main(int argc, char const *argv[]) {
  // Inicializa variaveis do programa
  // AlunosNAloc é a lista de alunos sem alocação, AlunosAloc é a lista de alunos alocados
  // QuartoVazio é a lista de quartos vazios e QuartoOcupado é a lista de quartos ocupados
  TipoFlags Flag;
  TipoListaAluno AlunoNAloc,AlunoAloc;
  TipoListaQuarto QuartoVazio,QuartoOcupado;
  struct timeval beginTime, endTime, beginT, endT;
  unsigned long time1, time2;
    
  // Procedimento de inicializacao das listas e das flags de impressao
  // Le dados de entrada inseridos pelo usuario
  // Obtem tempo entrada e alocacao de estruturas
  gettimeofday(&beginTime, NULL);
  int SemestreTotal = 0 ;
  Flag.Semestres = 0;
  Flag.Lista = 0;
  Flag.Tempo = 0;
  FLAluno(&AlunoNAloc);
  FLAluno(&AlunoAloc);
  FLQuarto(&QuartoVazio);
  FLQuarto(&QuartoOcupado);
  LeituraDeEntrada(&Flag,&QuartoVazio,&AlunoNAloc);
  gettimeofday(&endTime, NULL);
    
  // Processa dados obtidos no procedimento anterior
  // Obtem tempo de computacao
  gettimeofday(&beginT, NULL);
  TrabalhaDados(&QuartoVazio, &QuartoOcupado, &AlunoNAloc, &AlunoAloc, &SemestreTotal);
  gettimeofday(&endT, NULL);
    
  // Imprime resultados solicitados pelo usuario de acordo com as flags obtidas previamente
  if(Flag.Semestres){
    printf("%d\n",SemestreTotal); // Quantidade de semestres gastos para alocar todos os alunos
  }
  if(Flag.Lista){
    ImprimeAluno(AlunoAloc);      // Ordem de alocacao dos estudantes
  }
  if(Flag.Tempo){
    time1 = ((endT.tv_sec * 1000000 + endT.tv_usec) - (beginT.tv_sec * 1000000 + beginT.tv_usec));
    time2 = ((endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec));
    printf("%ld\n",time1);   // Tempo de computacao
    printf("%ld\n",time2);   // Tempo de entrada e alocacao de estruturas
  }

  // Libera memoria utilizada no programa
  FreeAll(&QuartoOcupado, &QuartoVazio, &AlunoAloc, &AlunoNAloc);

  return 0;                 // Fim de programa
}
