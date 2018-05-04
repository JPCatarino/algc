/*******************************************************************************
 Ficheiro de implementa��o do Tipo de Dados Abstracto SEQ_LIST (seqlist.c).
 A estrutura de dados de suporte da sequ�ncia � uma estrutura, constitu�da pelos
 campos de tipo inteiro Size para indicar o n�mero de elementos armazenados na
 sequ�ncia e os campos de tipo ponteiro para n�s de lista biligada Head e Tail,
 para representar, respectivamente, a cabe�a e a cauda da lista biligada onde
 s�o armazenados os n�meros inteiros.

 Autor : Jorge Ricardo Pinto de Figueiredo Catarino     MEC : 85028          
*******************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>


#include "seqlist.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Defini��o da Estrutura de Dados Interna da Sequ�ncia ************/

typedef struct binode *PtBiNode;
struct binode /* defini��o do n� da lista biligada */
{
	int Elem; /* o elemento da lista */
	PtBiNode PtPrev, PtNext; /* ponteiros para o n�s anterior e seguinte */
};

struct seqlist
{
  int Size; /* n�mero de elementos - sequence's size */
  PtBiNode Head; /* ponteiro para o in�cio da lista (cabe�a da lista) - list head */
  PtBiNode Tail; /* ponteiro para o fim da lista (cauda da lista) - list tail */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "sequencia(s) inexistente(s) - Sequence(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "indice errado - Wrong index",
                                 "elemento inexistente - Element does not exist",
                                 "sequencia vazia - Empty sequence",
                                 "sequencia cheia - Full sequence",
                                 "dimensao da sequencia errada - Wrong size",
                                 "ficheiro inexistente - File does not exist",
                                 "ponteiro nulo - Null pointer"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/******************** Prot�tipos dos Subprogramas Internos ********************/

PtBiNode BiNodeCreate (int);
void BiNodeDestroy (PtBiNode *);
void DoubleListDestroy (PtBiNode *);

/*************************** Defini��o das Fun��es ****************************/

void SeqListClearError (void)
{ Error = OK; }

int SeqListError (void)
{ return Error; }

char *SeqListErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqList SeqListCreate ()
{
  PtSeqList nList;

  if ((nList = malloc (sizeof (struct seqlist))) == NULL){
    Error = NO_MEM; return NULL; }
  
  nList->Head = NULL;
  nList->Tail = NULL;
  nList->Size = 0;
  Error = OK;
  return nList;
}

void SeqListDestroy (PtSeqList *pseq)
{
  PtSeqList tmpL = *pseq;
  if(tmpL == NULL){ Error = NO_SEQ; return;}
  DoubleListDestroy(&tmpL->Head);
  free(tmpL);
  Error = OK;
  *pseq = NULL;
}

PtSeqList SeqListCopy (PtSeqList pseq)
{
  PtSeqList Copy;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* cria��o da sequ�ncia copia nulo - creating an empty sequence */
  if ((Copy = SeqListCreate ()) == NULL) return NULL;

  /* fazer a copia da sequ�ncia - copying the components */
  for (PtBiNode Node = pseq->Head; Node != NULL; Node = Node->PtNext)
  {
    SeqListInsert (Copy, Node->Elem);
    if (Error == NO_MEM) break;
  }
  
  if (Error == NO_MEM) { SeqListDestroy (&Copy); return NULL; }
  
  Copy->Size = pseq->Size;
  Error = OK;
  return Copy;  /* devolve a sequ�ncia copia - returning the new sequence */
}

PtSeqList SeqListFileCreate (char *pfname)
{
  PtSeqList Seq; FILE *PtF; unsigned int Size, I; int Elem;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimens�o da sequ�ncia e do n�mero de elementos */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u", &Size);
  if (Size < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* cria��o da sequ�ncia vazia - creating an empty sequence */
  if ((Seq = SeqListCreate ()) == NULL) { fclose (PtF); return NULL; }

  Error = OK;
  /* leitura da sequ�ncia do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++)
  {
    fscanf (PtF, "%d", &Elem);
    SeqListInsert (Seq, Elem);
    if (Error == NO_MEM) break;
  }

  if (Error == NO_MEM) { SeqListDestroy (&Seq); return NULL; }

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  return Seq;  /* devolve a sequ�ncia criada - returning the new sequence */
}

void SeqListStoreFile (PtSeqList pseq, char *pfname)
{
  FILE *PtF;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequ�ncia tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita do n�mero de elementos armazenados na sequ�ncia */
  /* writing the number of elements */
  fprintf (PtF, "%u\n", pseq->Size);

  /* escrita da sequ�ncia - writing the sequence's components in the text file */
  for (PtBiNode Node = pseq->Head; Node != NULL; Node = Node->PtNext)
	fprintf (PtF, "%d\n", Node->Elem);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

int SeqListGetSize (PtSeqList pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0;}
  Error = OK;
  return pseq->Size;
}

int SeqListGetElement (PtSeqList pseq, int pindex)
{
  if(pindex > pseq->Size || pindex < -pseq->Size){
    Error = BAD_INDEX;
    return 0;
  }
  PtBiNode tmpNodeH = pseq->Head;
  PtBiNode tmpNodeT = pseq->Tail;
  int counter = 0;
  if(pindex >= 0){
    while(tmpNodeH != NULL){
    
      if(counter == pindex){
        Error = OK;
        return tmpNodeH->Elem;
      }
      counter++;
      tmpNodeH = tmpNodeH->PtNext;
    }
  }    
  else{
    counter = 1;
    while(tmpNodeT != NULL ){
      if(counter * -1 == pindex){
        Error = OK;
        return tmpNodeT->Elem;
      }
      counter++;
      tmpNodeT = tmpNodeT->PtPrev;
    }
  }
  return 0;
}

void SeqListSetElement (PtSeqList pseq, int pindex, int pvalue)
{
  if(pindex > pseq->Size || pindex < -pseq->Size){
    Error = BAD_INDEX;
    return ;
  }
  PtBiNode tmpNodeH = pseq->Head;
  PtBiNode tmpNodeT = pseq->Tail;
  int counter = 0;
  if(pindex >= 0){
    while(tmpNodeH != NULL){
    
      if(counter == pindex){
        Error = OK;
        tmpNodeH->Elem = pvalue;
      }
      counter++;
      tmpNodeH = tmpNodeH->PtNext;
    }
  }    
  else{
    counter = 1;
    while(tmpNodeT != NULL ){
      if(counter * -1 == pindex){
        Error = OK;
        tmpNodeT->Elem = pvalue;
      }
      counter++;
      tmpNodeT = tmpNodeT->PtPrev;
    }
  }
}

int SeqListEquals (PtSeqList pseq1, PtSeqList pseq2)
{
  if (pseq1 == NULL) { Error = NO_SEQ; return -1;}
  if (pseq2 == NULL) { Error = NO_SEQ; return -1;}
  int res = 0;

  if(pseq1->Size == pseq2->Size){
    int size = pseq1->Size;
    PtBiNode tmpN1 = pseq1->Head;
    PtBiNode tmpN2 = pseq2->Head;
    for(int i = 0; i < size;i++){
      if(tmpN1->Elem == tmpN2->Elem) res = 1;
      else{
        res = 0;
        break;
      }
      tmpN1 = tmpN1->PtNext;
      tmpN2 = tmpN2->PtNext;
    }
  }
  Error = OK;
  return res;
}

void SeqListInsert (PtSeqList pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return ;}
  PtBiNode nNode;

  if ((nNode = (PtBiNode) malloc (sizeof (struct binode))) == NULL)
	{ Error = NO_MEM; return; }

  nNode = BiNodeCreate(pvalue);
  nNode->PtNext = NULL;
  if(pseq->Head == NULL && pseq->Tail == NULL){
    pseq->Head = nNode;
    pseq->Tail = nNode;
    pseq->Size++;
    Error = OK;
    return;
  }
  else{
    nNode->PtPrev = pseq->Tail;
    pseq->Tail->PtNext = nNode;
    pseq->Tail = nNode;
    pseq->Size++;
    Error = OK;
  }
}


void SeqListDelete (PtSeqList pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return ;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  PtBiNode tmpNd = pseq->Head;
  PtBiNode auxNd;
  PtBiNode auxNd2;
  int tmpSi = pseq->Size;

  while(tmpNd != NULL){
    if(tmpNd->Elem == pvalue){
      if(tmpNd != pseq->Tail){
        auxNd = tmpNd->PtNext;
        if(tmpNd->PtPrev != NULL)
          auxNd->PtPrev = tmpNd->PtPrev;
        else  
          auxNd->PtPrev = NULL;
      }
      if(tmpNd != pseq->Head){
        auxNd2 = tmpNd->PtPrev;
        if(tmpNd->PtNext != NULL)
          auxNd2->PtNext = tmpNd->PtNext;
        else  
          auxNd2->PtNext = NULL;
      }
      if(pseq->Head == tmpNd){
        pseq->Head = auxNd;
      }
      if(pseq->Tail == tmpNd){
        pseq->Tail = auxNd2;
      }
      PtBiNode delNd = tmpNd;
      tmpNd = tmpNd->PtNext;
      BiNodeDestroy(&delNd);
      pseq->Size--;
    }
    else{
      tmpNd = tmpNd->PtNext;
    }
  }
  if(tmpSi == pseq->Size){
    Error = NO_NUMBER;
    return;
  }
  else  
    Error = OK;
}


int SeqListIsOrdered (PtSeqList pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int order = 1;
  PtBiNode tmpNd = pseq->Head;
  
  while(tmpNd != pseq->Tail){
    if(tmpNd->Elem > tmpNd->PtNext->Elem){
      order = 0;
      break;
    }
    tmpNd = tmpNd->PtNext;
  }
  Error = OK;
  return order;
}

int SeqListIsEvenOdd (PtSeqList pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int evenOdd = 1;
  PtBiNode tmpNd = pseq->Head;

  while(tmpNd != pseq->Tail){
    if(tmpNd->Elem  % 2 == 0){
      if(tmpNd->PtNext->Elem % 2 == 0){
        evenOdd = 0;
        break;
      }
    }
    else{
      if(tmpNd->PtNext->Elem % 2 != 0){
        evenOdd = 0;
      }
    }
    tmpNd = tmpNd->PtNext;
  }
  Error = OK;
  return evenOdd;
}

int SeqListNumberOfMultiples (PtSeqList pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int counter = 0;
  PtBiNode tmpNd = pseq->Head;

  while(tmpNd != NULL){
    if(tmpNd->Elem % pvalue == 0){
      counter++;
    }
    tmpNd = tmpNd->PtNext;
  }
  Error = OK;
  return counter;
}

void SeqListSmallerBigger (PtSeqList pseq, int * psmall, int * pbig)
{
  if (pseq == NULL) { Error = NO_SEQ; return;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return;}
  PtBiNode tmpNd = pseq->Head;

  if(SeqListIsOrdered(pseq)){
    *psmall = pseq->Head->Elem;
    *pbig = pseq->Tail->Elem;
  }
  else{
    int min  = INT_MAX;
    int max = INT_MIN;

    while(tmpNd != NULL){
      if(tmpNd->Elem<min) min = tmpNd->Elem;
      if(tmpNd->Elem>max) max = tmpNd->Elem;
      tmpNd = tmpNd->PtNext;
    }
    *psmall = min;
    *pbig = max;
    Error = OK;
  }
}

int SeqListIsPalindromic (PtSeqList pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int palindrome = 1;
  PtBiNode tmpNdH = pseq->Head;
  PtBiNode tmpNdT = pseq->Tail;
  
  while(tmpNdH != tmpNdT){
    if(tmpNdH->Elem != tmpNdT->Elem){
      palindrome = 0;
      break;
    }
    tmpNdH = tmpNdH->PtNext;
    tmpNdT = tmpNdT->PtPrev;
  }
  Error = OK;
  return palindrome;
}

double SeqListAverage (PtSeqList pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  double sum = 0;
  PtBiNode tmpNd = pseq->Head;
  while(tmpNd != NULL){
    sum += tmpNd->Elem;
    tmpNd = tmpNd->PtNext;
  }
  double average = sum / pseq->Size;
  Error = OK;
  return average;
}

/*******************************************************************************
 Fun��o auxiliar para criar um n� da lista biligada. Valores de erro: OK ou NO_MEM.
 
 Auxiliary function to create a binode. Error codes: OK or NO_MEM.
*******************************************************************************/

PtBiNode BiNodeCreate (int pelem)	/* aloca��o do n� */
{
	PtBiNode Node;

	if ((Node = (PtBiNode) malloc (sizeof (struct binode))) == NULL)
	{ Error = NO_MEM; return NULL; }

	Node->Elem = pelem;	/* copiar a informa��o */
	Node->PtPrev = NULL;	/* apontar para detr�s para NULL */
	Node->PtNext = NULL;	/* apontar para a frente para NULL */

	Error = OK;
	return Node;
}

/*******************************************************************************
 Fun��o auxiliar para libertar um n� da lista biligada. Valores de erro: OK ou NULL_PTR.
 
 Auxiliary function to free a binode. Error codes: OK or NULL_PTR.
*******************************************************************************/
void BiNodeDestroy (PtBiNode *pnode)	/* liberta��o do n� */
{
	if (*pnode == NULL) { Error = NULL_PTR; return; }
	free (*pnode);	/* liberta��o do n� */
	*pnode = NULL;	/* colocar o ponteiro a nulo */
	Error = OK;
}

/*******************************************************************************
 Fun��o auxiliar para destruir uma lista biligada. Valores de erro: OK ou NULL_PTR.
 
 Auxiliary function to destroy a double link list. Error codes: OK or NULL_PTR.
*******************************************************************************/
void DoubleListDestroy (PtBiNode *phead)
{
	PtBiNode TmpHead = *phead; PtBiNode Node;

	if (TmpHead == NULL) { Error = NULL_PTR; return; }
	while (TmpHead != NULL)
	{
		Node = TmpHead; TmpHead = TmpHead->PtNext;
		BiNodeDestroy (&Node);
	}
	Error = OK; 
}
