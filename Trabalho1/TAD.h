#ifndef TAD
#define TAD
#define TRUE 1
#define FALSE 0

// Tipos

typedef long TipoNumero;
typedef int TipoSemestre;
typedef int TipoExigencia;
typedef int TipoNota;
typedef int TipoOferecido;
typedef int bool;

typedef struct Flags_str {
  char Semestres;
  char Lista;
  char Tempo;
} TipoFlags;

typedef struct TipoAluno {
  TipoNumero    Chave;
  TipoSemestre  Semestre;
  TipoExigencia Exigencia;
  TipoOferecido Oferecido;
} TipoAluno;

typedef struct TipoAluno *ApontadorAluno;

typedef struct TipoQuarto {
  TipoNumero Chave;
  TipoNota   Nota;
  ApontadorAluno Ocupado;
} TipoQuarto;

typedef struct Celula_str_aluno  *ApontadorCelulaAluno;
typedef struct Celula_str_quarto *ApontadorCelulaQuarto;

typedef struct Celula_str_aluno {
  TipoAluno  Aluno;
  ApontadorCelulaAluno Prox;
} CelulaAluno;

typedef struct Celula_str_quarto {
  TipoQuarto  Quarto;
  ApontadorCelulaQuarto Prox;
} CelulaQuarto;

typedef struct {
  ApontadorCelulaAluno Primeiro, Ultimo;
} TipoListaAluno;

typedef struct {
  ApontadorCelulaQuarto Primeiro, Ultimo;
} TipoListaQuarto;

#endif

// Funcoes implementadas em TAD.c
void FLAluno(TipoListaAluno *Lista);
void FLQuarto(TipoListaQuarto *Lista);
void InsereAluno(TipoAluno Aluno, TipoListaAluno *Lista);
void InsereQuarto(TipoQuarto Quarto, TipoListaQuarto *Lista);
int VaziaAluno(TipoListaAluno Lista);
int VaziaQuarto(TipoListaQuarto Lista);
void ImprimeQuarto (TipoListaQuarto Lista);
void ImprimeAluno (TipoListaAluno Lista);
void FimDoSemestre(TipoListaAluno *AlunoNAloc,TipoListaAluno *AlunoAloc,TipoListaQuarto *ListaQuartoVazio);
void AlocaAlunoQuarto(TipoListaAluno *AlunoNAloc,TipoListaQuarto *ListaQuartoVazio, TipoListaAluno *ListaAlunoAloc, TipoListaQuarto *ListaQuartoOcupado);
void MoveListaQuartoDesocupou(TipoListaQuarto *ListaQuartoOcupado, TipoListaQuarto *ListaQuartoVazio);
void TrabalhaDados(TipoListaQuarto *QuartoVazio, TipoListaQuarto *QuartoOcupado, TipoListaAluno *AlunoNAloc, TipoListaAluno *AlunoAloc, int *SemestreTotal);
void FreeAll(TipoListaQuarto *ListaQuartoOcupado,TipoListaQuarto *ListaQuartoVazio,TipoListaAluno *ListaAlunoAloc, TipoListaAluno *ListaAlunoNAloc);

// Funcoes implementadas em leitura.c
int ComparaDados(char *token, TipoFlags *Flags);
void LeituraDeEntrada(TipoFlags *Flags,TipoListaQuarto *QuartoVazio,TipoListaAluno *AlunoNAloc);
