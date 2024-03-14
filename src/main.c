/* Input da tastiera impostato di default.
   Per impostare le condizioni iniziali modificare le condizioni iniziali dalle "#define" in main.c.
   Input da riga di comando non ancora implementato. */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define INPUT 1
#define CORRECT 1 
#define WRONG 1/3
#define TOT 33
#define MIN 18
#define ROUND 1

float calcolaPunteggio(int giuste, int sbagliate, float punteggioGiusta, float penalita);
void calcolaCombinazioni(int totDomande, float punteggioGiusta, float penalita, float min, int arrotondamento);
void stampaCombinazione(int giuste, int sbagliate, int nonDate, float risultato, float risultatoArrotondato, float min, int promosso);

int main(){
    int tot=TOT, arrotondamento=ROUND, continua=1;
    float giusta=(float)CORRECT, sbagliata=(float)WRONG, min=(float)MIN;
    char s[50];
    
    #if INPUT
    printf("number of questions: ");   scanf("%d", &tot);
    printf("minimum score to pass: "); scanf("%f", &min);
    printf("correct answer value: ");  scanf("%f", &giusta);
    printf("wrong answer penalty: ");  scanf("%f", &sbagliata);
    while(continua){
        printf("is the score rounded to get the final mark [Y/n]? "); scanf("%s", s);
        if(strcmp(s, "Y")!=0 && strcmp(s, "n")!=0) printf("'%s' is not valid, insert 'Y' or 'n'\n", s);
        else{
            arrotondamento=strcmp(s, "Y")==0;
            continua=0;
        }
    }
    printf("\n");
    #endif
    
    calcolaCombinazioni(tot, giusta, sbagliata<0?-sbagliata:sbagliata, min, arrotondamento);
    return 0;
}

void stampaCombinazione(int giuste, int sbagliate, int nonDate, float risultato, float risultatoArrotondato, float min, int promosso){
    printf("correct: %2d, wrong: %2d, not given: %2d", giuste, sbagliate, nonDate);
    printf(" -> mark: %6.2f ~ %6.2f %s", risultato, risultatoArrotondato, promosso?">=":"< ");
    printf(" %5.2f -> %s\n", min, promosso?"test passed":"test not passed (!)");
}

float calcolaPunteggio(int giuste, int sbagliate, float punteggioGiusta, float penalita){
    return (float)((float)giuste*punteggioGiusta-(float)sbagliate*penalita);
}

void calcolaCombinazioni(int totDomande, float punteggioGiusta, float penalita, float min, int arrotondamento){
    int giuste, sbagliate, nonDate, promosso;
    float risultato, risultatoArrotondato;
    
    for(giuste=0;giuste<=totDomande;giuste++){
        for(sbagliate=0;sbagliate<=totDomande-giuste;sbagliate++){
            nonDate=totDomande-(giuste+sbagliate);
            risultato=calcolaPunteggio(giuste, sbagliate, punteggioGiusta, penalita);
            risultatoArrotondato=arrotondamento?round(risultato):risultato;
            promosso=risultatoArrotondato>=min?1:0;
            stampaCombinazione(giuste, sbagliate, nonDate, risultato, risultatoArrotondato, min, promosso);
        }
    }
}

