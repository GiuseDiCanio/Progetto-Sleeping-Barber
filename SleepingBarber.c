#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> 

#define CLIENTI_MASSIMI 50

void * cliente(void * num);
void * barbiere(void * );
void randwait(int secondi);

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

    for (i = 0; i < numClienti; i++) {
        pthread_join(tid[i], NULL);
        sleep(1);
    }

        tuttoFatto = 1;
        sem_post( & cuscinoBarbiere);
        pthread_join(btid, NULL);
    }

void * cliente(void * numero) {
  int num = *(int * )numero;
  sem_wait( & stanzaAttesa);
  printf("CLIENTE %d : ***E' ENTRATO NELLA SALA D'ATTESA.\n", num + 1);
  
  sem_wait( & poltronaBarbiere);
  
  sem_post( & stanzaAttesa);
 
  printf("CLIENTE %d : ***RISVEGLIA IL BARBIERE.\n", num + 1);
  sem_post( & cuscinoBarbiere);
 
  sem_wait( & taglio);
  
  sem_post( & poltronaBarbiere);
  printf("CLIENTE %d : ***LASCIA IL NEGOZIO.\n", num + 1);
}

void * barbiere(void * junk) {
  while (!tuttoFatto) {
    printf("BARBIERE : ***DORME...\n");
    sem_wait( & cuscinoBarbiere);
    if (!tuttoFatto) {
      printf("BARBIERE : ***STA TAGLIANDO I CAPELLI\n");
      randwait(2);
      printf("BARBIERE : ***HA FINITO DI TAGLIARE I CAPELLI\n");
      sem_post( & taglio);
    } else {
      printf("BARBIERE : ***PUO' ANDARE A CASA PER OGGI.\n");
    }
  }
}

void randwait(int secondi) {
  int len;
  len = (int)((1 * secondi) + 1);
  sleep(len);
}
