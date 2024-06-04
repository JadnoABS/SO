#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

typedef struct filosofo {
  int indice;
  enum {pensando, faminto, comendo} status;
  pthread_t thread;
} filosofo;

typedef struct {
  int value;
} semaforo;

filosofo** filosofos;
semaforo** garfos;

void exibirStatus() {
  printf("Filosofos: ");
  for(int i = 0; i < N; i++) {
    printf("%2d", filosofos[i]->indice);
  }
    printf("\nStatus:    ");
  for(int i = 0; i < N; i++) {
      printf("%2d", filosofos[i]->status);
  }
  printf("\n\n");
}

void wait(semaforo* S) {
  while(S->value <= 0) {
  }
  S->value--;
}

void signal(semaforo* S) {
  S->value++;
}

void comer(filosofo* F) {
  exibirStatus();
  F->status = comendo;
  sleep(1);
}

void pensar(filosofo* F) {
  exibirStatus();
  F->status = pensando;
}

void* querComer(filosofo* F) {
  exibirStatus();
  F->status = faminto;
  wait(garfos[F->indice]);
  wait(garfos[(F->indice + 1) % N]);

  comer(F);

  signal(garfos[F->indice]);
  signal(garfos[(F->indice + 1) % N]);

  pensar(F);
}

void initFilosofos(filosofo** F, int n) {
  for(int i = 0; i < n; i++){
    F[i] = (filosofo*) malloc(sizeof(filosofo));
    F[i]->status = pensando;
    F[i]->indice = i;
  }
}

void initGarfos(semaforo** G, int n) {
  for(int i = 0; i < n; i++){
    G[i] = (semaforo*) malloc(sizeof(semaforo));
    G[i]->value = 1;
  }
}


int main() {

  filosofos = (filosofo**) malloc(sizeof(filosofo*) * N);
  garfos = (semaforo**) malloc(sizeof(semaforo*) * N);

  for(int i = 0; i < N; i++){
    filosofos[i] = (filosofo*) malloc(sizeof(filosofo));
    filosofos[i]->status = pensando;
    filosofos[i]->indice = i;
  }

  for(int i = 0; i < N; i++){
    garfos[i] = (semaforo*) malloc(sizeof(semaforo));
    garfos[i]->value = 1;
  }

  exibirStatus();

  for(int i = 0; i < N; i++) {
    pthread_create(&filosofos[i]->thread, NULL, querComer, filosofos[i]);
    pthread_join(filosofos[i]->thread, NULL);
  }

  return 0;
}


