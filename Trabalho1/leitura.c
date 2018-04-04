#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TAD.h"

/*Para ser possivel a manipulação das entradas, criamos o arquivo leitura o qual é responsavel pela recepção dos dados e manipulação dos mesmos.
Conforme consta nas definições de entradas do projeto, receberemos strings as quais selecionarão as saidas desejadas.
Tais strings serão "semestres" para que a saída seja a quantidade total de semestres gastos para alocar todos os alunos, "lista" para imprimir a
lista na ordem em que os alunos foram alocados, "tempo" para imprimir o tempo de execução do programa e "tudo" para que seja impresso
todas as opções anteriores.
*/

/*Para a manipulação das entradas em strings, utilizamos o parâmetro "%[^\n]%*c" no scanf para que seja possivel a obtenção de toda a string digitada no
sdtin até o enter ser apertado. Após isso utilizamos a função strtok para separar as palavras recebidas e chamamos a função "ComparaDados" para cada palavra.
A função "ComparaDados" recebe como parâmetro cada palavra e a struct "TipoFlags", onde criamos uma flag pra cada palavra chave.
Desta forma, se aparecer as palavras "semestres","lista" ou "tempo", setamos a Flag para 1,podendo assim analisar quais saidas foram pedidas,e se
for escrito "tudo", todas as Flags serão setadas para 1 para que todas as saidas sejam selecionadas.Porem, se escrever algo que nao se encaixa nas
palavras-chaves, o programa pedirá um novo input apos uma mensagem de erro, estando assim preso em um loop ate que se escreva uma das palavras
definidas.
*/

int ComparaDados(char *token, TipoFlags *Flags){
  if (!strcmp(token,"semestres")) {     // Se inseriu semestres, seta flag de impressao de semestres
    Flags->Semestres = 1;
  } else if (!strcmp(token,"lista")) {  // Se inseriu lista, seta flag de impressao de lista
    Flags->Lista = 1;
  } else if (!strcmp(token,"tempo")) {  // Se inseriu tempo, seta flag de impressao de tempo
    Flags->Tempo = 1;
  } else if (!strcmp(token,"tudo")) {   // Seta todas as flags para 1. Nao ha mais possibilidades de setar flags. Retorno 1.
    Flags->Semestres = 1;
    Flags->Lista = 1;
    Flags->Tempo = 1;
    return 1;
  } else {// Esse caso somente será acionado se for digitado algo que nao seja palavra chave, fazendo o retorno da função ser 2
    Flags->Semestres = 0;
    Flags->Lista = 0;
    Flags->Tempo = 0;
    return 2;
  }
  return 0; // Retorna 0 em caso padrao.
}

void LeituraDeEntrada(TipoFlags *Flags,TipoListaQuarto *QuartoVazio,TipoListaAluno *AlunoNAloc){
    volatile int i;
    int  numApt, numEst;
    char *palavra;
    char input[30];
    TipoQuarto Quarto;
    TipoAluno Aluno;

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

     // Leitura de Numero de Apartamentos e Numero de Estudantes
     do {
      scanf("%d %d", &numApt, &numEst);
     } while (!(numApt>=0 && numEst>=0));

     /* Leitura de Dados dos Apartamentos, criamos o TipoQuarto Quarto, o qual receberá a o valor do estado de conservação e salvará em Quarto.Nota,
     salvará em Quarto.Chave(que será o numero do quarto) o valor de i+1 pois i começa em zero e o ponteiro Quarto.Ocupado, que se ocupado aponta para o Aluno
     que o ocupa, aponta para NULL*/
     for (i = 0; i < numApt; i++){
        scanf("%d", &Quarto.Nota);
        Quarto.Chave= i+1;
        Quarto.Ocupado = NULL;
        InsereQuarto(Quarto,QuartoVazio);
     }

     for (i = 0; i < numEst; i++){
        scanf("%d %d",&Aluno.Exigencia, &Aluno.Semestre);
        Aluno.Chave = i+1;
        Aluno.Oferecido = 0;
        InsereAluno(Aluno,AlunoNAloc);
     }
}
