#include <error.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int count;
int vez;

void secao_critica(int id) {
  count++;
  printf("Processo %d na secao critica\n", id);
  printf("\tcount: %d\n", count);
  sleep(1);
}

void secao_nao_critica(int id) {
  printf("Processo %d na secao nao critica\n", id);
}

void *p1() {
  int meu_id = 0;
  int outro = 1;
  while (true) {
    while (vez != meu_id) {
    };
    secao_critica(meu_id);
    vez = outro;
    secao_nao_critica(meu_id);
  }
}

void *p2() {
  int meu_id = 1;
  int outro = 0;
  while (true) {
    while (vez != meu_id) {
    };
    secao_critica(meu_id);
    vez = outro;
    secao_nao_critica(meu_id);
  }
}

int main() {

  count = 0;
  vez = 0;

  pthread_t filhos[2];
  pthread_create(&filhos[0], NULL, p1, NULL);
  pthread_create(&filhos[1], NULL, p2, NULL);
  pthread_join(filhos[0], NULL);
  pthread_join(filhos[1], NULL);

  return 0;
}
