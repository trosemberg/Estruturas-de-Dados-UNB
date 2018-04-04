#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TAD.h"

// Faz lista de alunos vazia
void FLAluno(TipoListaAluno *Lista){
  Lista->Primeiro = (ApontadorCelulaAluno) malloc(sizeof(CelulaAluno));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

// Faz lista de quartos vazia
void FLQuarto(TipoListaQuarto *Lista){
  Lista->Primeiro = (ApontadorCelulaQuarto) malloc(sizeof(CelulaQuarto));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

// Insere aluno na lista de alunos
void InsereAluno(TipoAluno Aluno, TipoListaAluno *Lista){
  Lista->Ultimo->Prox = (ApontadorCelulaAluno) malloc(sizeof(CelulaAluno));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Aluno = Aluno;
  Lista->Ultimo->Prox = NULL;
}

// Insere quarto na lista de quartos
void InsereQuarto(TipoQuarto Quarto, TipoListaQuarto *Lista){
  Lista->Ultimo->Prox = (ApontadorCelulaQuarto) malloc(sizeof(CelulaQuarto));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Quarto = Quarto;
  Lista->Ultimo->Prox = NULL;
}

// Averigua se lista de alunos esta vazia. Retorna 1 em caso afirmativo.
int VaziaAluno(TipoListaAluno Lista){
  return (Lista.Primeiro == Lista.Ultimo);
}

// Averigua se lista de quartos esta vazia. Retorna 1 em caso afirmativo.
int VaziaQuarto(TipoListaQuarto Lista){
  return (Lista.Primeiro == Lista.Ultimo);
}

// Imprime, em ordem, a chave dos alunos em uma lista
void ImprimeAluno (TipoListaAluno Lista){
  ApontadorCelulaAluno aux;
  aux = Lista.Primeiro->Prox;
  if(aux==NULL){
    return;
  }
  while(aux!=NULL){
    printf("%ld\n",aux->Aluno.Chave);
    aux = aux->Prox;
  }
}

// Imprime os dados dos quartos de uma lista
void ImprimeQuarto (TipoListaQuarto Lista){
  ApontadorCelulaQuarto aux;
  aux = Lista.Primeiro->Prox;
  if(aux==NULL){
    printf("Lista Vazia\n");
    return;
  }
  while(aux!=NULL){
    printf("O Quarto numero:%ld e estado:%d\n",aux->Quarto.Chave,aux->Quarto.Nota);
    if((aux->Quarto.Ocupado)==NULL){
      printf("Esta desocupado\n");
    }
    else{
      printf("Esta ocupado\n");
    }
    aux = aux->Prox;
  }
}

// Função responsavel por decrementar o Aluno.Semestre de todas as listas e o Aluno.Exigencia da lista AlunoNAloc em menos 5 pois o semestre acabou
void FimDoSemestre(TipoListaAluno *AlunoNAloc,TipoListaAluno *AlunoAloc,TipoListaQuarto *ListaQuartoVazio){
  ApontadorCelulaAluno FimSemestreANA,FimSemestreAA; // Fim do semestre para os alunos nao alocados e para alunos alocado, respectivamente.
  FimSemestreANA = AlunoNAloc->Primeiro->Prox;  // Primeiro aluno nao alocado
  FimSemestreAA  = AlunoAloc->Primeiro->Prox;   // Primeiro aluno alocado
  while(FimSemestreANA != NULL){              // Enquanto nao chegar ao ultimo aluno nao alocado
    if(FimSemestreANA->Aluno.Oferecido == 1){   // Caso se tenha oferecido ao menos um quarto
      FimSemestreANA->Aluno.Exigencia -=5;      // Decrementar em 5 a exigencia do aluno (desespero)
      FimSemestreANA->Aluno.Oferecido = 0;      // Reseta flags setadas
    }
    FimSemestreANA = FimSemestreANA->Prox;    // Avancar aluno
  }
  while(FimSemestreAA != NULL){                 // Enquanto nao chegar ao ultimo aluno alocado
   FimSemestreAA->Aluno.Semestre -=1;           // Decrementar numero de semestres restantes
   FimSemestreAA->Aluno.Oferecido = 0;         // Reseta flags setadas
   FimSemestreAA = FimSemestreAA->Prox;         // Avancar aluno
  }
}

/*Função responsavel pela a alocação dos alunos nos apartamento. Conforme o enunciado, Primeiro um Quarto é oferecido a todos os alunos
para depois ir ao proximo*/

void AlocaAlunoQuarto(TipoListaAluno *AlunoNAloc,TipoListaQuarto *ListaQuartoVazio, TipoListaAluno *ListaAlunoAloc, TipoListaQuarto *ListaQuartoOcupado){
  ApontadorCelulaAluno AuxAluno1, AuxAluno2;    // Inicializa ponteiro para alunos
  ApontadorCelulaQuarto AuxQuarto1, AuxQuarto2; // Inicializa ponteiro para quartos
  AuxAluno1 = AlunoNAloc->Primeiro;             // Celula cabeca da lista de alunos nao alocados
  AuxAluno2 = AuxAluno1->Prox;                  // Primeiro aluno da lista de alunos nao alocados
  AuxQuarto1 = ListaQuartoVazio->Primeiro;      // Celula cabeca da lista de quartos vazios
  AuxQuarto2 = AuxQuarto1->Prox;                // Primeiro quarto da lista de quartos vazios
  if(AuxAluno2==NULL){ // Caso em que a lista de alunos nao alocados ficou vazia:
    return;            // Finalizar
  }
  while((AuxQuarto2)!=NULL){    // Enquanto nao chegar ao ultimo quarto da lista, continuar
    if(AuxAluno2!=NULL){                // Se ha um quarto valido e um aluno valido:
      AuxAluno2->Aluno.Oferecido = 1;   // Flag que indica que um quarto foi oferecido ao aluno
    }
    if((AuxQuarto2->Quarto.Nota)>=AuxAluno2->Aluno.Exigencia){ // Se aluno tiver exigencia menor q o estado do quarto, aloque-o
      // O quarto a ser ocupado recebe as informacoes do aluno que o ocupara
      AuxQuarto2->Quarto.Ocupado = &AuxAluno2->Aluno;
      // Transfere o Aluno da lista de alunos nao alocados para a lista de alunos alocados
      AuxAluno1->Prox = AuxAluno2->Prox;                      // Elimina o aluno alocado da lista de alunos nao alocados
      ListaAlunoAloc->Ultimo->Prox = AuxAluno2;               // Transfere o aluno alocado para a lista de alunos alocados
      ListaAlunoAloc->Ultimo = ListaAlunoAloc->Ultimo->Prox;  // Atualiza o ultimo aluno da lista de alunos alocados
      ListaAlunoAloc->Ultimo->Prox = NULL;                    // "Aterra" o final da lista de alunos alocados
      if (AuxAluno1->Prox == NULL) {      // Caso seja o ultimo aluno:
        AlunoNAloc->Ultimo = AuxAluno1;   // Atualiza o ultimo aluno da lista de alunos nao alocados
      }
      if (VaziaAluno(*AlunoNAloc)){       // Se nao ha mais alunos para alocar, finalizar
        return;                           // Finalizar
      }
      // Transfere o Quarto da lista de quartos vazios para a lista de quartos ocupados
      AuxQuarto1->Prox = AuxQuarto2->Prox;                    // Elimina o quarto ocupado da lista de quartos vazios
      ListaQuartoOcupado->Ultimo->Prox = AuxQuarto2;          // Transfere o quarto ocupado para a lista de quartos ocupados
      ListaQuartoOcupado->Ultimo = ListaQuartoOcupado->Ultimo->Prox;  // Atualiza o ultimo quarto da lista de ocupados
      ListaQuartoOcupado->Ultimo->Prox = NULL;                // "Aterra" o final da lista de quartos ocupados
      if (AuxQuarto1->Prox == NULL) {           // Caso seja o ultimo quarto:
        ListaQuartoVazio->Ultimo = AuxQuarto1;  // Atualiza o ultimo quarto da lista de desocupados
      }
      // Move os ponteiros para continuar a tentativa de alocar alunos
      AuxAluno1 = AlunoNAloc->Primeiro;         // Retorna a primeira celula da lista de nao alocados
      AuxAluno2 = AuxAluno1->Prox;              // Retorna ao primeiro aluno da lista de nao alocados
      AuxQuarto2 = AuxQuarto1->Prox;            // Avanca para o proximo quarto disponivel da lista
    } else if((AuxAluno2->Prox)==NULL){         // Se chegar ao ultimo aluno da lista, volta ao primeiro e avanca um quarto
      AuxAluno1 = AlunoNAloc->Primeiro;         // Celula cabeca da lista de alunos nao alocados
      AuxAluno2 = AuxAluno1->Prox;              // Primeiro aluno da lista de alunos nao alocados
      AuxQuarto1 = AuxQuarto2;                  // Avanca um quarto
      AuxQuarto2 = AuxQuarto2->Prox;            // Anda um quarto, pois como auxquarto2!=NULL ainda existe auxquarto2->prox
    }
    else{                                       // Caso seja uma varredura falha padrao, avanca para o proximo aluno
      AuxAluno1 = AuxAluno2;                    // Avanca um aluno
      AuxAluno2 = AuxAluno2->Prox;              // Avanca um aluno, pois como auxaluno2!=NULL ainda existe auxaluno2->prox
    }
  }
}

// Move quartos que acabaram de ser desocupados para a lista de quartos vazios
void MoveListaQuartoDesocupou(TipoListaQuarto *ListaQuartoOcupado, TipoListaQuarto *ListaQuartoVazio){
  ApontadorCelulaQuarto p,q;        // Inicializa ponteiro para quarto
  p = ListaQuartoOcupado->Primeiro; // Aponta para celula cabeca
  q = p->Prox;                      // Aponta para o primeiro quarto Ocupado
  if(q == NULL){                    // Caso a lista esteja vazia
    return;                         // Finalizar
  }
  while(q != NULL){                 // Enquanto nao chegar ao final da lista de quartos ocupados
    if( ((q->Quarto.Ocupado)->Semestre) == 0 ){ // Averiguar se aluno finalizou o curso (deve-se desocupar quarto)
        p->Prox = q->Prox;                      // Elimina quarto da lista de quartos ocupados
        ListaQuartoVazio->Ultimo->Prox = q;     // Transfere o quarto para a lista de quartos desocupados
        ListaQuartoVazio->Ultimo = ListaQuartoVazio->Ultimo->Prox;  // Atualiza o ultimo quarto da lista de vazios
        ListaQuartoVazio->Ultimo->Prox = NULL;  // "Aterra" o final da lista de quartos vazios
        if (p->Prox == NULL) {            // Caso seja o ultimo quarto:
          ListaQuartoOcupado->Ultimo = p; // Atualiza o ultimo quarto da lista de quartos ocupados
        }
        q = p->Prox;       // Avanca um quarto
    } else {               // Se nao desocupou o quarto, averiguar o proximo
      p = q;               // Avanca apontador
      q = q->Prox;         // Avanca quarto
    }
  }
}

// Função responsavel pelas manipulações das listas e parte logica do programa, a partir dos dados obtidos em LeituraDeEntrada
void TrabalhaDados(TipoListaQuarto *QuartoVazio, TipoListaQuarto *QuartoOcupado, TipoListaAluno *AlunoNAloc, TipoListaAluno *AlunoAloc, int *SemestreTotal){
  do{                                                                  // Roda ao menos uma vez
    *SemestreTotal +=1;                                                // Incrementa a quantidade de semestres transcorridos
    AlocaAlunoQuarto(AlunoNAloc,QuartoVazio,AlunoAloc,QuartoOcupado);  // Aloca os alunos sem quarto nos quartos possiveis
    FimDoSemestre(AlunoNAloc,AlunoAloc,QuartoVazio);                   // Decrementa semestre nos alocados e padrao nos nao alocado caso tenha quarto vazio
    MoveListaQuartoDesocupou(QuartoOcupado,QuartoVazio);               // Quartos desocupados sao transferidos para a lista correta
  }while(!VaziaAluno(*AlunoNAloc));                                    // Tenta alocar alunos ate que todos tenham um quarto
}

// Funcao responsavel por liberar a memoria alocada dinamicamente
void FreeAll(TipoListaQuarto *ListaQuartoOcupado,TipoListaQuarto *ListaQuartoVazio,TipoListaAluno *ListaAlunoAloc, TipoListaAluno *ListaAlunoNAloc){
//COMEÇA A DAR FREE EM TUDO QUE FOI USADO NO TRABALHO
  ApontadorCelulaAluno AuxAluno;
  ApontadorCelulaQuarto AuxQuarto;
    
//DAR FREE EM TUDO QUE RESTA NA LISTA DE ALUNOS NAO ALOCADOS
  free(ListaAlunoNAloc->Primeiro);
  ListaAlunoNAloc->Primeiro = NULL;
  ListaAlunoNAloc->Ultimo = NULL;
//TERMINA DE DAR FREE NA LISTA DE ALUNOS NAO ALOCADOS

//COMEÇA A DAR FREE NA LISTA DE ALUNOS ALOCADOS
  while(ListaAlunoAloc->Primeiro->Prox != NULL){
    AuxAluno = ListaAlunoAloc->Primeiro;
    while(AuxAluno->Prox != ListaAlunoAloc->Ultimo){
      AuxAluno = AuxAluno->Prox;
    }
    free(AuxAluno->Prox);
    ListaAlunoAloc->Ultimo = AuxAluno;
    AuxAluno->Prox = NULL;
  }
  free(ListaAlunoAloc->Primeiro);
  ListaAlunoAloc->Primeiro = NULL;
  ListaAlunoAloc->Ultimo = NULL;
  AuxAluno = NULL;
//TERMINA DE DAR FREE NA LISTA DE ALUNOS ALOCADOS

//COMEÇA A DAR FREE NA DE QUARTOS ALOCADOS
  while(ListaQuartoOcupado->Primeiro->Prox != NULL){
    AuxQuarto = ListaQuartoOcupado->Primeiro;
    while(AuxQuarto->Prox != ListaQuartoOcupado->Ultimo){
      AuxQuarto = AuxQuarto->Prox;
    }
    free(AuxQuarto->Prox);
    ListaQuartoOcupado->Ultimo = AuxQuarto;
    AuxQuarto->Prox = NULL;
  }
  free(ListaQuartoOcupado->Primeiro);
  ListaQuartoOcupado->Primeiro = NULL;
  ListaQuartoOcupado->Ultimo = NULL;
  AuxQuarto = NULL;
//TERMINA DE DAR FREE NA LISTA DE QUARTOS ALOCADOS

//COMEÇA A DAR FREE NA DE QUARTOS LIVRES
  while(ListaQuartoVazio->Primeiro->Prox != NULL){
    AuxQuarto = ListaQuartoVazio->Primeiro;
    while(AuxQuarto->Prox != ListaQuartoVazio->Ultimo){
      AuxQuarto = AuxQuarto->Prox;
    }
    free(AuxQuarto->Prox);
    ListaQuartoVazio->Ultimo = AuxQuarto;
    AuxQuarto->Prox = NULL;
  }
  free(ListaQuartoVazio->Primeiro);
  ListaQuartoVazio->Primeiro = NULL;
  ListaQuartoVazio->Ultimo = NULL;
  AuxQuarto = NULL;
//TERMINA DE DAR FREE NA LISTA DE QUARTOS LIVRES

}
