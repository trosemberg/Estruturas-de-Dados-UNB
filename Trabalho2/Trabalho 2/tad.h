#ifndef TAD
#define TAD
#define TRUE 1
#define FALSE 0

// Tipos
typedef struct Flags_str {
  char Passos;
  char Tempo;
} TipoFlags;

typedef int bool;
typedef int TipoIndice;
typedef int TipoDist;
typedef char TipoChave;
typedef char TipoPorta;
typedef enum TipoCor{
  BRANCO = 0, CINZA, PRETO
} TipoCor;

typedef struct TipoCelulaAdj *ApCelulaAdj;
typedef struct TipoCelulaAdj {
    TipoIndice  Vertice;   // Indice da lista de adjacencia
    ApCelulaAdj P;
} TipoCelulaAdj;

typedef struct TipoVertice {
    ApCelulaAdj Primeiro;  // Ponteiro para o primeiro da lista
    TipoCor     Cor;
    TipoIndice  Pai;
    TipoDist    Dist;
    TipoChave   Chave;
    TipoPorta   Porta;
} TipoVertice;

typedef struct TipoVertice *ApTipoVertice;
typedef struct TipoGrafo {
    int V;
    int E;
    int K;
    int D;
    TipoChave* KeyLog;
    ApTipoVertice Adj;
} TipoGrafo;

typedef TipoGrafo *Grafo;

typedef struct CelulaQ* ApCelulaQ;

typedef struct CelulaQ {
  int QVertice;
  ApCelulaQ   Prox;
} CelulaQ;

typedef struct {
  ApCelulaQ Primeiro, Ultimo;
} Queue;

#endif

int ComparaDados(char *token, TipoFlags *Flags);
Grafo FazGrafo(int V, int E, int K, int D);
void FazQ(Queue *Q);
void AdicionaQ(Queue *Q, int S);
Queue InicializaQ(Grafo G, int s);
int VaziaQ(Queue Q);
int RetiraQ(Queue *Q);
void ImprimeQ(Queue Q);
void AdicionaVertice(Grafo G, int v0, int vd);
void AdicionaChave(Grafo G, int vi, char ki);
void AdicionaPorta(Grafo G, int vi, char di);
int ConvIndicePorta(TipoPorta d0, int K);
int ConvIndiceChave(TipoChave k0, int K);
int PassaPorta(Grafo G, int v0);
int NovaChave(Grafo G, int v0);
void AtualizaKeyLog(Grafo G, int v0);
int Minimo(int a, int b);
Grafo GrafoCopia(Grafo G,Grafo G_copia);
int bfs(Grafo G, int s, int g);
int bfs1(Grafo G, int s, int g);
int bfs2(Grafo G, int s, int g, int distbfs1);
Grafo LeituraDeEntrada(TipoFlags *Flags, int *inicio, int *saida);
void freeQ(Queue *Q);
void freelista(TipoCelulaAdj *L,int v);
void freeG(Grafo G);
