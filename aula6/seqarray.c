/*******************************************************************************
 Ficheiro de implementa��o do Tipo de Dados Abstracto SEQ_ARRAY (seqarray.c).
 A estrutura de dados de suporte da sequ�ncia � um registo, constitu�da pelos
 campos de tipo inteiro Dim para indicar a capacidade de armazenamento da 
 sequ�ncia e Size para indicar o n�mero de elementos efectivamente armazenados na
 sequ�ncia e o campo de tipo ponteiro Seq, para representar a sequ�ncia (array) 
 atribu�da dinamicamente onde s�o armazenados os n�meros inteiros.

 Autor : Jorge Ricardo Pinto de Figueiredo Catarino          NMEC : 85028           
*******************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

#include "seqarray.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Defini��o da Estrutura de Dados Interna da Sequ�ncia ************/

struct seqarray
{
  unsigned int Dim; /* capacidade de armazenamento - array's size */
  int Size; /* n�mero de elementos - sequence's size */
  int *Seq; /* ponteiro para armazenar a sequencia - array to store the numbers */
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
                                 "ficheiro inexistente - File does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/*************************** Defini��o das Fun��es ****************************/

void SeqArrayClearError (void)
{ Error = OK; }

int SeqArrayError (void)
{ return Error; }

char *SeqArrayErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqArray SeqArrayCreate (unsigned int pdim)
{
  // checking dim
  if (pdim < 1) { Error = BAD_SIZE; return NULL;}
  PtSeqArray pArr;
  
  // checking memory
  if ((pArr = malloc (sizeof (struct seqarray))) == NULL){
    Error = NO_MEM; return NULL; }
  
  pArr->Dim = pdim;
  pArr->Size = 0;
  pArr->Seq = malloc(sizeof(int) * pdim);
  Error = OK;

  return pArr;
}

void SeqArrayDestroy (PtSeqArray *pseq)
{
  PtSeqArray tempSeq = *pseq;
  if(tempSeq == NULL){ Error = NO_SEQ; return;}
  free(tempSeq);
  Error = OK;
  *pseq = NULL;   
}

PtSeqArray SeqArrayCopy (PtSeqArray pseq)
{
  PtSeqArray Copy; int I;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* cria��o da sequ�ncia copia vazia - creating an empty sequence */
  if ((Copy = SeqArrayCreate (pseq->Dim)) == NULL) return NULL;

  /* fazer a copia dos elementos da sequ�ncia - copying the components */
  for (I = 0; I < pseq->Size; I++) Copy->Seq[I] = pseq->Seq[I];
  Copy->Size = pseq->Size;

  return Copy;  /* devolve a sequ�ncia copia - returning the new sequence */
}

PtSeqArray SeqArrayFileCreate (char *pfname)
{
  PtSeqArray Seq; FILE *PtF; unsigned int Dim, Size, I;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimens�o da sequ�ncia e do n�mero de elementos armazenados */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u %u", &Dim, &Size);
  if (Dim < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* cria��o da sequ�ncia com a dimens�o pretendida - creating the sequence */
  if ((Seq = SeqArrayCreate (Dim)) == NULL) { fclose (PtF); return NULL; }

  /* leitura da sequ�ncia do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++) fscanf (PtF, "%d", Seq->Seq+I);
  Seq->Size = Size;

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  Error = OK;
  return Seq;  /* devolve a sequ�ncia criada - returning the new sequence */
}

void SeqArrayStoreFile (PtSeqArray pseq, char *pfname)
{
  FILE *PtF; unsigned int I;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequ�ncia tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimens�o da sequ�ncia e do n�mero de elementos armazenados na sequ�ncia */
  /* writing the sequence's dimension and the number of elements */
  fprintf (PtF, "%u %u\n", pseq->Dim, pseq->Size);

  /* escrita da sequ�ncia - writing the sequence's components in the text file */
  for (I = 0; I < pseq->Size; I++) fprintf (PtF, "%d\n", pseq->Seq[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

int  SeqArrayGetDimension (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  Error = OK;
  return pseq->Dim;
}

int SeqArrayGetSize (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  Error = OK;
  return pseq->Size;
}

int SeqArrayGetElement (PtSeqArray pseq, int pindex)
{
  if(pindex > pseq->Size || pindex < -pseq->Size){
    Error = BAD_INDEX;
    return 0;
  }
  else if(pindex >= 0){
    Error = OK;
    return pseq->Seq[pindex];
  }
  else{
    Error = OK;
    return pseq->Seq[pseq->Size + pindex];
  }
}

void SeqArraySetElement (PtSeqArray pseq, int pindex, int pvalue)
{
  if(pindex > pseq->Size || pindex < -pseq->Size){
  Error = BAD_INDEX;
  return;
  }
  if(pindex >= 0){
    Error = OK;
    pseq->Seq[pindex] = pvalue;
  }
  else{
    Error = OK;
    pseq->Seq[pseq->Size + pindex] = pvalue;
  }
}

int SeqArrayEquals (PtSeqArray pseq1, PtSeqArray pseq2)
{
  if (pseq1 == NULL) { Error = NO_SEQ; return -1;}
  if (pseq2 == NULL) { Error = NO_SEQ; return -1;}
  int res = 0;
  if(pseq1->Size == pseq2->Size){
    int size = pseq1->Size;
    for(int i = 0;i<size;i++){
      if(pseq1->Seq[i] == pseq2->Seq[i]) res=1;
      else{
        res = 0;
        break;
      }
    }
  }
  Error = OK;
  return res;
}

void SeqArrayInsert (PtSeqArray pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return; }
  else if(pseq->Size < pseq->Dim){
    pseq->Seq[pseq->Size] = pvalue;
    pseq->Size++;
    Error = OK;
  }
  else{
    Error = SEQ_FULL;
    return;
  }
}

void SeqArrayDelete (PtSeqArray pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return; }
  if (pseq->Size == 0) {Error = SEQ_EMPTY; return;}
  int tmpSize = pseq->Size;
  for(int j = 0; j < pseq->Size; j++){
    if(pseq->Seq[j] == pvalue){
      for(int i = j; i < pseq->Size; i++){
        pseq->Seq[i] = pseq->Seq[i+1];
      }
      pseq->Size--;
      j--;
      Error = OK;
    }
  }
  if(tmpSize == pseq->Size){
    Error = NO_NUMBER;
    return;
  }
  
}

void SeqArrayDuplicate (PtSeqArray pseq)
{
  int *newSeq;
  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return; }
  
  /* verifica se a sequ�ncia n�o est� vazia - verifies if sequence is not empty */  
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return; }
 
  if ((newSeq = calloc (2*pseq->Size, sizeof (int))) == NULL)
  { Error = NO_MEM; return; }
  
  pseq->Dim = 2*pseq->Size;  /* armazenamento da nova dimens�o - storing the new dimension */

  /* copiar os elementos - copying the elements */
  for (int I = 0; I < pseq->Size; I++) newSeq[I] = pseq->Seq[I];
  /* guardar o novo array e libertar o antigo - storing the new arry and freeing the old */
  int * Tmp = pseq->Seq; pseq->Seq = newSeq; free (Tmp);
  
  Error = OK;
}

int SeqArrayIsOrdered (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int order = 1;
  for(int i = 0; i < pseq->Size - 1; i++){
    if(pseq->Seq[i] > pseq->Seq[i+1]){
      order = 0;
      break;
    }
  }
  Error = OK;
  return order;
}

int SeqArrayIsEvenOdd (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int evenOdd = 1;
  for(int i = 0; i < pseq->Size - 1; i++){
    if(pseq->Seq[i]  % 2 == 0){
      if(pseq->Seq[i + 1] % 2 == 0){
        evenOdd = 0;
        break;
      }
    }
    else{
      if(pseq->Seq[i+1] % 2 != 0){
        evenOdd = 0;
      }
    }
  }
  Error = OK;
  return evenOdd;
}

int SeqArrayNumberOfMultiples (PtSeqArray pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int counter = 0;
  for(int i = 0; i < pseq->Size; i++){
    if(pseq->Seq[i] % pvalue == 0){
      counter++;
    }
  }
  Error = OK;
  return counter;
}

void SeqArraySmallerBigger (PtSeqArray pseq, int * psmall, int * pbig)
{
  if (pseq == NULL) { Error = NO_SEQ; return;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return;}
  
  if(SeqArrayIsOrdered(pseq)){
    *psmall  = pseq->Seq[0];
    *pbig    = pseq->Size;
    Error = OK;
  }
  else{
    int min  = INT_MAX;
    int max = INT_MIN;

    for(int i = 0; i < pseq->Size; i++){
      if(pseq->Seq[i]<min) min = pseq->Seq[i];
      if(pseq->Seq[i]>max) max = pseq->Seq[i];
    }
    *psmall = min;
    *pbig = max;
    Error = OK;
  }
}

int SeqArrayIsPalindromic (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  int palindrome = 1;
  for(int i = 0; i < pseq->Size / 2; i++){
    if(pseq->Seq[i] != pseq->Seq[(pseq->Size - 1) - i]){
      palindrome = 0;
      break;
    }
  }
  Error = OK;
  return palindrome;
}

double SeqArrayAverage (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return -1;}
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return -1;}
  double sum = 0;
  for(int i = 0; i < pseq->Size; i++){
    sum += pseq->Seq[i];
  }
  double average = sum / pseq->Size;
  Error = OK;
  return average;
}
