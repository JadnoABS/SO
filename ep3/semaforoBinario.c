#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct proc {
  int id;
  struct proc* next;
} process;

typedef struct {
  int value;
  process* line;
} semaphore;


void initSemaphore(semaphore* S);
void wait(semaphore* S, process* P);
void signal(semaphore* S);
void block(semaphore* S, process* P);
void wake(semaphore* S);
void execute(semaphore* S, process* P);


void initSemaphore(semaphore* S) {
  S->value = 1;
  S->line = NULL;
}

void wait(semaphore* S, process* P) {
  if(S->value <= 0) {
    block(S, P);
    return;
  }
  S->value--;
  execute(S, P);
}

void signal(semaphore* S) {
  S->value++;
  if(S->value > 0) {
    wake(S);
  }
}

void block(semaphore* S, process* P) {
  P->next = NULL;
  if(!S->line){ // Primeiro na fila
    S->line = P;
    return;
  }

  process* prc = S->line;
  while(prc->next){ // Procurar o final da fila
    prc = prc->next;
  }

  prc->next = P; // Insere no final da fila
  return;
}

void wake(semaphore* S) { // Acorda o primeiro processo da fila
  if(S->line){
    S->value--;
    process* p = S->line;
    S->line = S->line->next;
    execute(S, p);
  }
}

void execute(semaphore* S, process* P) {
  printf("Executando o processo %d\n", P->id);
  sleep(1);
  printf("Terminando a execucao do processo %d\n", P->id);
  signal(S);
}


int main() {

  semaphore* sem = (semaphore*) malloc(sizeof(semaphore));
  initSemaphore(sem);

  process* proc1 = (process*) malloc(sizeof(process));
  proc1->id = 1;
  process* proc2 = (process*) malloc(sizeof(process));
  proc2->id = 2;
  process* proc3 = (process*) malloc(sizeof(process));
  proc3->id = 3;

  wait(sem, proc1);
  wait(sem, proc2);
  wait(sem, proc3);

  return 0;
}

