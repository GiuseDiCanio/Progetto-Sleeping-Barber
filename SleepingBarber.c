#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define CLIENTI_MASSIMI 50


int main(int argc, char * argv[]) {
    pthread_t btid;
    pthread_t tid[CLIENTI_MASSIMI];
    int i, numClienti, numeroSedie;
    int Numero[CLIENTI_MASSIMI];
    

    printf("INSERISCI IL NUMERO DI CLIENTI(Max 50) : ");
    scanf("%d", & numClienti);
    printf("INSERISCI IL NUMERO DELLE SEDIE: ");
    scanf("%d", & numeroSedie);

    if (numClienti > CLIENTI_MASSIMI) {
    printf("IL NUMERO MASSIMO DI CLIENTI E' %d.\n", CLIENTI_MASSIMI);
    exit(-1);
  }

  for (i = 0; i < CLIENTI_MASSIMI; i++) {
    Numero[i] = i;
  }
  
}
