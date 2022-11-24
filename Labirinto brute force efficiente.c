#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 28
#define MAX 10000

//definizione dei tipi necessari
typedef enum {MURO, LIBERO, START, END, POSITION} stato;

//inizializzazione
int i,j,casuale, scelta, contatore = 0, gioco = 0;
stato *posizione, *inizio, *fine, labirinto[DIM][DIM];

//prototipi di funzione
void riempi(stato m[DIM][DIM]);

void riempibordi(stato m[DIM][DIM]);

void stampa (stato m[DIM][DIM]);

void spazio();

int check(stato *p, stato *q);

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int main()
{
    //creazione labirinto
    srand(time(NULL));
    riempi(labirinto);
    riempibordi(labirinto);
    stampa (labirinto);

    //posto iniziale
    do
    {

        do
        {
            puts("Inserire riga di inizio:");
            scanf("%d", &i);
        }
        while(i<1 || i>DIM);

        do
        {
            puts("Inserire colonna di inizio:");
            scanf("%d", &j);
        }
        while(j<1 || j>DIM);

        inizio = &labirinto[i-1][j-1];
    }
    while(*inizio == 0);

    *inizio = START;

    //visualizzazione
    spazio();
    stampa (labirinto);

    //posto finale
    do
    {

        do
        {
            puts("Inserire riga di fine:");
            scanf("%d", &i);
        }
        while(i<1 || i>DIM);

        do
        {
            puts("Inserire colonna di fine:");
            scanf("%d", &j);
        }
        while(j<1 || j>DIM);

        fine = &labirinto[i-1][j-1];
    }
    while(*fine == 0);

    *fine = END;

    //visualizzazione
    spazio();
    stampa (labirinto);

    //algoritmo di gioco
    posizione = inizio;

    while(gioco == 0 && contatore<MAX)
    {
        casuale = rand()%4;

        if(casuale == 0 && *(posizione+1) != MURO)
        {
            posizione += 1;
        }
        else if(casuale == 1 && *(posizione+DIM) != MURO)
        {
            posizione += DIM;
        }
        else if(casuale == 2 && *(posizione-1) != MURO)
        {
            posizione -= 1;
        }
        else if(casuale == 3 && *(posizione-DIM) != MURO)
        {
            posizione -= DIM;
        }

        *posizione = POSITION;

        gioco = check(posizione, fine);

        //visualizzazione del risultato del tentativo
        spazio();
        stampa (labirinto);
        delay(1);

        contatore++;
    }

    //situazioni finali
    if(gioco == 0)
    {
        puts("Il labirinto non e' stato concluso, numero massimo di mosse superato.");
    }
    else if(gioco == 1)
    {
        puts("Il labirinto e' stato completato entro il numero massimo di mosse.");
        printf("Numero di mosse: %d", contatore);
    }
}

//funzioni

void riempi(stato m[DIM][DIM])
{
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            m[i][j] = rand()%2;
        }
    }
}

void riempibordi(stato m[DIM][DIM])
{
    for(i=0; i<DIM; i++)
    {
        m[i][0] = 0;
        m[i][DIM-1] = 0;
        m[0][i] = 0;
        m[DIM-1][i] = 0;
    }
}

void stampa (stato m[DIM][DIM])
{
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if(m[i][j]==0)
            {
                printf("%c", 219);
                printf("%c", 219);
            }
            else if(m[i][j]==1)
            {
                printf("%c", 176);
                printf("%c", 176);
            }
            else if (m[i][j]==2)
            {
                printf("%c", 3);
                printf("%c", 3);
            }
            else if (m[i][j]==3)
            {
                printf("%c", 60);
                printf("%c", 62);
            }
            else if (m[i][j]==4)
            {
                printf("%c", 1);
                printf("%c", 1);
            }
        }
        puts(" ");
    }
}

void spazio()
{
    for(i=0; i<25; i++)
    {
        puts(" ");
    }
}

int check(stato *p, stato *q)
{
    if(p == q)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
