#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> 

#define CLIENTI_MASSIMI 50

sem_t stanzaAttesa;

sem_t poltronaBarbiere;

sem_t cuscinoBarbiere;

sem_t taglio;

int tuttoFatto = 0;

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

  sem_init( & stanzaAttesa, 0, numeroSedie);
  sem_init( & poltronaBarbiere, 0, 1);
  sem_init( & cuscinoBarbiere, 0, 0);
  sem_init( & taglio, 0, 0);

    pthread_create( & btid, NULL, barbiere, NULL);

    for (i = 0; i < numClienti; i++) {
        pthread_create( & tid[i], NULL, cliente, (void * ) & Numero[i]);
        sleep(1);
      }
  
}
