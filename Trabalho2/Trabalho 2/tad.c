#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

Grafo FazGrafo(int V, int E, int K, int D){
   int v, k;
   Grafo G = (Grafo) malloc(sizeof(TipoGrafo));
   G->V = V;
   G->E = E;
   G->K = K;
   G->D = D;
   // Incializar lista de Chaves
   G->KeyLog = (TipoChave*) malloc(K * sizeof(TipoChave));
   for (k = 0; k < K; k++) {
     G->KeyLog[k] = 0;
   }
   // Inicializa lista de Adjacencia
   G->Adj = (ApTipoVertice) malloc(V * sizeof(TipoVertice));
   for (v = 0; v < V; ++v){
       G->Adj[v].Primeiro = NULL;
       G->Adj[v].Cor      = BRANCO;
       G->Adj[v].Dist     = -1;
       G->Adj[v].Chave    = 0;
       G->Adj[v].Porta    = 0;
   }
   return G;
}



void FazQ(Queue *Q){
  Q->Primeiro = (ApCelulaQ) malloc(sizeof(CelulaQ));
  Q->Ultimo = Q->Primeiro;
  Q->Primeiro->Prox = NULL;
}

void AdicionaQ(Queue *Q, int S){
  Q->Ultimo->Prox = (ApCelulaQ) malloc(sizeof(CelulaQ));
  Q->Ultimo = Q->Ultimo->Prox;
  Q->Ultimo->QVertice = S;
  Q->Ultimo->Prox = NULL;
}

Queue InicializaQ(Grafo G, int s){
  Queue Q;
  FazQ(&Q);
  AdicionaQ(&Q, s);
  if(G->Adj[s].Dist == -1){
    G->Adj[s].Dist = 0;
  }
  return Q;
}

int VaziaQ(Queue Q){
  return (Q.Primeiro == Q.Ultimo);
}

int RetiraQ(Queue *Q){
  ApCelulaQ q;
  int item;
  if (VaziaQ(*Q)) {
    printf("Erro em RetiraQ\n");
    return -1;
  }
  q = Q->Primeiro->Prox;
  item = q->QVertice;
  Q->Primeiro->Prox = q->Prox;
  if (Q->Primeiro->Prox == NULL)
    Q->Ultimo = Q->Primeiro;
  free(q);
  return item;
}

void ImprimeQ(Queue Q){
  ApCelulaQ aux;
  aux = Q.Primeiro->Prox;
  if(aux==NULL){
    return;
  }
  while(aux!=NULL){
    printf("%d\n",aux->QVertice);
    aux = aux->Prox;
  }
}

void AdicionaVertice(Grafo G, int v0, int vd){
  // Adicionar novo vertice
  ApCelulaAdj NCel = (ApCelulaAdj) malloc(sizeof(TipoCelulaAdj));
  NCel->Vertice = vd;
  NCel->P = G->Adj[v0].Primeiro;
  G->Adj[v0].Primeiro = NCel;
  // Grafo nao direcional, fazer o inverso
  NCel = (ApCelulaAdj) malloc(sizeof(TipoCelulaAdj));
  NCel->Vertice = v0;
  NCel->P = G->Adj[vd].Primeiro;
  G->Adj[vd].Primeiro = NCel;
}

void AdicionaChave(Grafo G, int vi, char ki){
  G->Adj[vi].Chave = ki;
}

void AdicionaPorta(Grafo G, int vi, char di){
  G->Adj[vi].Porta = di;
}


/*
Converter porta para indice de keylog
A -> 0
B -> 1
...
Retorna -1 em caso de erro
*/
int ConvIndicePorta(TipoPorta d0, int K){
  int conv;
  conv = (int) d0-65;
  if(conv >= K || conv < 0){
    printf("Erro em ConvIndicePorta\n");
    return -1;
  } else {
    return conv;
  }
}

/*
Converter chave para indice de keylog
a -> 0
b -> 1
...
Retorna -1 em caso de erro
*/
int ConvIndiceChave(TipoChave k0, int K){
  int conv;
  conv = (int) k0-97;
  if(conv >= K || conv < 0){
    printf("Erro em ConvIndiceChave\n");
    return -1;
  } else {
    return conv;
  }
}

// Verificar se ha porta e se como abri-la
int PassaPorta(Grafo G, int v0){
  // Se existir uma Porta
  if(G->Adj[v0].Porta != 0){
    // Conferir se ha uma Chave em Keylog
    // Chamar funcao que converte char da porta em indice do keylog
    if (G->KeyLog[ConvIndicePorta(G->Adj[v0].Porta, G->K)] != 0) {
        // Retorna 1 se ha Chave
        return 1;
    } else {
        // Retorna 0 c.c.
        return 0;
    }
  } else {
    // Se nao ha porta, returna 1
    return 1;
  }
}

// Verificar se ha Chave nova
int NovaChave(Grafo G, int v0){
  // Se ha Chave
  if(G->Adj[v0].Chave != 0){
    // Verificar se a chave é nova
    if(G->KeyLog[ConvIndiceChave(G->Adj[v0].Chave, G->K)] != 0) {
      // Se ja possuia a chave, retorna 0
      return 0;
    } else {
      // Se é nova, retorna 1 (obs. NAO atualizar keylog aqui!)
      return 1;
    }
  } else {
    // Se nao ha chave, retorna 0
    return 0;
  }
}

// Atualiza KeyLog
void AtualizaKeyLog(Grafo G, int v0){
  G->KeyLog[ConvIndiceChave(G->Adj[v0].Chave, G->K)] = 1;
}

// Identifica o minimo
int Minimo(int a, int b){
  if (b == -1) {
    return a;
  } else if (a == -1) {
    return b;
  } else if (a < b) {
    return a;
  } else {
    return b;
  }
}

Grafo GrafoCopia(Grafo G, Grafo G_copia){
  int v, k;
  G_copia->V = G->V;
  G_copia->E = G->E;
  G_copia->K = G->K;
  G_copia->D = G->D;
  // Incializar lista de Chaves
  for (k = 0; k < G->K; ++k) {
    G_copia->KeyLog[k] = G->KeyLog[k];
  }
  // Inicializa lista de Adjacencia
  for (v = 0; v < G->V; ++v){
      G_copia->Adj[v].Primeiro = G->Adj[v].Primeiro;
      G_copia->Adj[v].Cor   = BRANCO;
      G_copia->Adj[v].Dist  = G->Adj[v].Dist;
      G_copia->Adj[v].Chave = G->Adj[v].Chave;
      G_copia->Adj[v].Porta = G->Adj[v].Porta;
  }
  return G_copia;
}

int bfs(Grafo G, int s, int g){
	int distbfs1 = -1; //variavel pra armazenar a distancia do primeiro bfs(bfs1)
	int distbfs2 = -1;//variavel para armazenar distancia do segundo bfs(bfs2)
	int distFinal;
	Grafo G_copia;//faz uma copia do Grafo passado no começo do programa
	G_copia = (Grafo) malloc(sizeof(TipoGrafo));
  G_copia->KeyLog = (TipoChave*) malloc(G->K * sizeof(TipoChave));
  G_copia->Adj = (ApTipoVertice) malloc(G->V * sizeof(TipoVertice));
  G_copia = GrafoCopia(G, G_copia);
	distbfs1 = bfs1(G, s, g);//aplica bfs1 no grafo passado no começo do programa
	distbfs2 = bfs2(G_copia, s, g, distbfs1);//aplica bfs2 na copia do grafo passado no começo do programa recebendo como parametro 
	                                         //o menor caminho do primeiro bfs,limitando as pesquisas de melhor caminho
                                           //para no maximo o numero de passos necessario para resolver o programa com o primeiro bfs
                                           //desta forma bfs2 nao varre todas as camadas do grafo, varre apenas ate uma dada largura
  free(G_copia->KeyLog );
	free(G_copia->Adj);
	free(G_copia);
	distFinal = Minimo(distbfs2, distbfs1);
	return distFinal;
}
/*Primeiro bfs implementado. Faz o BFD tentando achar o caminho minimo sem possuir nenhuma chave, armazena a posiçao da primeira chave encontrada
e continua o BFS tentando achar a saida sem precisar dela. Se achar a saida, limita os proximos BFS para uma largura maxima igual a encontrada.
Apos terminar o BFS inicial, Faz um BFS a partir da posição da primeira chave encontrada, abrindo as portas equivalentes a ela para tentar diminuir
o numero necessario de passos para completar o labirinto, armazendo a posiçao da primeira chave encontrada, continuando recursivamente. Desta forma 
nao necessariamente será necessario achar todas as chaves, pois uma chave pode estar a uma distancia da entrada maior que a necessaria para completar
o labirinto sem ela, logo ela não sera encontrada. */
int bfs1(Grafo G, int s, int g){
  int u,flag=0,x;
  int distInterna = -1;
  int distRecursiva = -1;
  int distFinal;
  Grafo G_copia;
  ApCelulaAdj v;

  Queue Q = InicializaQ(G, s);
  while (!VaziaQ(Q)) {
    u = RetiraQ(&Q);
    // NovaChave (Abrir nova bfs paralelamente, caso encontre nova chave)
    if( NovaChave(G, u) && flag==0){
    	G_copia = (Grafo) malloc(sizeof(TipoGrafo));
    	G_copia->KeyLog = (TipoChave*) malloc(G->K * sizeof(TipoChave));
  		G_copia->Adj = (ApTipoVertice) malloc(G->V * sizeof(TipoVertice));
  		flag=1;
  		x=u;
  	}
    if( PassaPorta(G, u) ){     // (Matar branch se n passar da porta)
    	for (v = G->Adj[u].Primeiro; v != NULL; v = v->P){      //caso a saida seja encontrada, o .dist do vertice sera atualizado
        	if ( G->Adj[v->Vertice].Cor == BRANCO ) {           //para o numero de passos necessarios para chegar ate ela, a posição GrafoCopia
          		G->Adj[v->Vertice].Cor  = CINZA;                //mantem essa distancia, salva no grafo copiado, desta forma podendo usar esse 
          		G->Adj[v->Vertice].Dist = G->Adj[u].Dist + 1;   //valor como numero de passos limitantes a cada pesquisa, conforme podemos observar
          		G->Adj[v->Vertice].Pai  = u;                    //na linha de codigo  abaixo "if((G->Adj[u].Dist > G->Adj[g].Dist) && (G->Adj[g].Dist > 0))"
          		AdicionaQ(&Q, v->Vertice);
        	}
      	}
    }
    if((G->Adj[u].Dist > G->Adj[g].Dist) && (G->Adj[g].Dist > 0)){
      break;
    }
    G->Adj[u].Cor = PRETO;
    if(u == g){
      break;
    }
  }
  if(flag==1){
  	G_copia = GrafoCopia(G, G_copia);            // Copiar G: G' <- G
    AtualizaKeyLog(G_copia, x);
    distRecursiva = bfs1(G_copia, x, g); // Abrir nova bfs
  };
  distInterna = G->Adj[g].Dist;
  distFinal = Minimo(distInterna, distRecursiva);
  if(flag==1){
    free(G_copia->Adj);
    free(G_copia->KeyLog);
    free(G_copia);
  };
  freeQ(&Q);
  return distFinal;
}
/*Esta função aplica o algoritimo de BFS, porem iniciando um novo BFS a partir do momento que encontra uma chave e atualiza o Keylog do  
grafo incluindo a chave encontrada, desta forma o BFS deveria testar todos os caminhos possiveis para encontrar o menor deles.
Porem a BFS esta recebendo como parametro a distancia minima necessaria para achar a saida encontrada pelo BFS1, limitando o a distancia que o BFS2
pode pesquisar. Desta forma, se o BFS nao tiver achado a saida e chegar a uma distancia maior que a encontrada BFS1, esse caminho ja é descartado
como menor caminho, o que diminui bruscamente a quantidade testes necesaarios para encontrar a resposta */
int bfs2(Grafo G, int s, int g,int distbfs1){
  int u,flag = 0;
  int distInterna = -1;
  int distRecursiva = -1;
  int distRecursiva_old = -1;
  int distFinal;
  Grafo G_copia;
  ApCelulaAdj v;
  Queue Q = InicializaQ(G, s);
  while (!VaziaQ(Q)) {
    u = RetiraQ(&Q);
    // NovaChave (Abrir nova bfs paralelamente, caso encontre nova chave)
    if( NovaChave(G, u) && flag==0){
      G_copia = (Grafo) malloc(sizeof(TipoGrafo));
      G_copia->KeyLog = (TipoChave*) malloc(G->K * sizeof(TipoChave));
      G_copia->Adj = (ApTipoVertice) malloc(G->V * sizeof(TipoVertice));
      flag=1;
    }
    if( NovaChave(G, u) ){
      G_copia = GrafoCopia(G, G_copia);            // Copiar G: G' <- G
      AtualizaKeyLog(G_copia, u);
      distRecursiva_old = distRecursiva;
      distRecursiva = bfs2(G_copia, u, g, distbfs1); // Abrir nova bfs
      distRecursiva = Minimo(distRecursiva_old, distRecursiva);
    }
    else if( PassaPorta(G, u) ){     // (Matar branch se n passar da porta)
      for (v = G->Adj[u].Primeiro; v != NULL; v = v->P){
        if ( G->Adj[v->Vertice].Cor == BRANCO ) {
          G->Adj[v->Vertice].Cor  = CINZA;
          G->Adj[v->Vertice].Dist = G->Adj[u].Dist + 1;
          G->Adj[v->Vertice].Pai  = u;
          AdicionaQ(&Q, v->Vertice);
        }
      }
    }
    if((G->Adj[u].Dist > distbfs1) || ((G->Adj[u].Dist > G->Adj[g].Dist) && (G->Adj[g].Dist > 0))){
      break;
    }
    G->Adj[u].Cor = PRETO;
    if(u == g){
      break;
    }
  }
  distInterna = G->Adj[g].Dist;
  distFinal = Minimo(distInterna, distRecursiva);
  if(flag == 1){
    free(G_copia->Adj);
    free(G_copia->KeyLog);
    free(G_copia);
  }
  freeQ(&Q);
  return distFinal;
}


// A utility function to print the adjacenncy list representation of graph
void printGrafo(Grafo G)
{
    int v;

    for (v = 0; v < G->V; ++v)
    {
        printf("Distancia %d   ", G->Adj[v].Dist);
        ApCelulaAdj pCrawl = G->Adj[v].Primeiro;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->Vertice);
            pCrawl = pCrawl->P;
        }
        printf("\n");
    }
}

void freeQ(Queue *Q){
  // Enquanto a lista nao estiver vazia, retirar elemento
  while (!VaziaQ(*Q)){
    RetiraQ(Q);
  }
 free(Q->Primeiro);
}

void freelista(TipoCelulaAdj *L,int v){
  ApCelulaAdj aux;
  if(L->P==NULL){
    free(L);
  }
  else{
    while(L->P !=NULL){
      aux = L->P;
      L->P = aux->P;
      free(aux);
    }
    free(L);  
  }
}



void freeG(Grafo G){
  int v;
  for (v = 0; v < G->V; ++v){
  freelista(G->Adj[v].Primeiro,v);
  }
  free(G->Adj);
  free(G->KeyLog);
  free(G);
}
