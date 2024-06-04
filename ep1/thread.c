#include <error.h>
#include <pthread.h>
#include <stdio.h>

// Funcao que cada thread ira rodar quando criada
void *run() { printf("Hello World!\n"); }

int main() {
  // Vetor para as 5 threads
  pthread_t filhos[5];

  // Criacao de threads
  for (int i = 0; i < 5; i++) {
    pthread_create(&filhos[i], NULL, run, NULL);
  }

  return 0;
}
