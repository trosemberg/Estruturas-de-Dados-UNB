#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tad.h"

int ComparaDados(char *token, TipoFlags *Flags){
  if (!strcmp(token,"passos")) {
    // Se inseriu semestres, seta flag de impressao de semestres
    Flags->Passos = 1;
  } else if (!strcmp(token,"tempo")) {
     // Se inseriu tempo, seta flag de impressao de tempo
    Flags->Tempo = 1;
  } else if (!strcmp(token,"tudo")) {
    // Seta todas as flags para 1. Nao ha mais possibilidades de setar flags.
    Flags->Passos = 1;
    Flags->Tempo = 1;
    return 1;
  } else {
    // Esse caso somente será acionado se for digitado algo que
    // nao seja palavra chave, fazendo o retorno da função ser 2
    Flags->Passos = 0;
    Flags->Tempo = 0;
    return 2;
  }
  return 0; // Retorna 0 em caso padrao.
}

Grafo LeituraDeEntrada(TipoFlags *Flags, int *inicio, int *saida){
    volatile int i;
    char *palavra;
    char input[30];
    int V, E, K, D, I, S;
    int a, b;
    char c;
    /*O do while a seguir funciona da seguinte forma, ele escaneara o input todo ate o /n desprezando o mesmo. Depois checará a presença das palavras
    chaves, se elas nao ocorrerem ou ocorrer alguma palavra que nao é chave, apitara msg de erro e pedira para entrar com os parametros de entrada novamente.
    Caso identifique em algum momento a palavra chave tudo, ele automaticamente sai do do while e se identificar palavras chaves(diferentes de tudo) ele irá
    setar as flags comparando com a chave e assim que o strtok varrer todas as palavras chaves, ele sairá da função do while
    */
    do{
    scanf("%[^\n]%*c",input);
    palavra = strtok(input," ");
      while(palavra != NULL)
      {
        if(ComparaDados(palavra, Flags)==1){// Se o retorno da função comparadados for 1, logo a palavra tudo foi digitada nao precisado mais ler nada
          break;
        }else if ((ComparaDados(palavra, Flags))==2){// Foi digitado algo q nao é palavra chave, msg de erro e sai do loop de analise de token
          printf("Uma das palavras nao consta no registro de palavras-chaves\nFavor redigitar os parametros de entrada\n");
          break;
        }
       palavra = strtok (NULL, " ");
      }
      if(palavra == NULL)break;
    }while((ComparaDados(palavra, Flags))==2);// Faz toda a analise novamente com novo scanf caso tenha sido digitado algo q nao seja palavra chave

    // Leitura do Numero de Vertices e Numero de Arestas
    do {
     scanf("%d %d", &V, &E);
    } while (!(V>=0 && E>=0));

   // Leitura do Numero de Chaves e Numero de Portas
   do {
    scanf("%d %d", &K, &D);
   } while (!(K>=0 && D>=0));

   // Faz Grafo com os dados apresentados
   Grafo G = FazGrafo(V, E, K, D);

    // Leitura da Posicao Inicial e Saida do labirinto
    do {
     scanf("%d %d", &I, &S);
   } while (!(I>=0 && S>=0));


   // Leitura de E pares que representam as conexoes dos vertices
   for (i = 0; i < E; i++) {
     scanf("%d %d", &a, &b);
     AdicionaVertice(G, a, b);
   }

   // Leitura de K pares que representam as chaves
   for (i = 0; i < K; i++) {
     scanf("%d %c", &a, &c);
     AdicionaChave(G, a, c);
   }

   // Leitura de D pares que representam as portas
   for (i = 0; i < D; i++) {
     scanf("%d %c", &a, &c);
     AdicionaPorta(G, a, c);
   }

   // Saida de dados
   *inicio = I;
   *saida = S;
   return G;
}
