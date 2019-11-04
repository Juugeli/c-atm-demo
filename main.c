#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tulostaTiedot(char[256], double);
double nostaRahaa(double);
double laitaRahaa(double);
void lueRoskat(void);

int main() {

    FILE * PANKKITILI;

    double TILIN_SALDO;
    char TILINUMERO[256];
    char TILINUMERO_KOPIO[256];
    char PIN[256];
    char OIKEA_PIN[256];
    int valinta;
    int lopetus = 0;

    printf("Anna tilinumero: ");
    scanf("%s", TILINUMERO);
    lueRoskat();

    strcpy(TILINUMERO_KOPIO, TILINUMERO);
    strcat(TILINUMERO, ".tili");

    printf("Anna PIN-koodi: ");
    scanf("%s", PIN);
    lueRoskat();

    if((PANKKITILI = fopen(TILINUMERO, "r")) == NULL){
        printf("Jokin meni vikaan, yrita uudestaan!");
        exit(0);
    }

    fscanf(PANKKITILI, "%s", OIKEA_PIN);

    if (strcmp(PIN, OIKEA_PIN)!= 0){

        printf("PIN meni vaarin!\n");
        printf("Yrita uudestaan.");
        exit(0);
    }

    fscanf(PANKKITILI, "%lf", &TILIN_SALDO);
    fclose(PANKKITILI);

    while(lopetus == 0){

        printf("\nMita haluat tehda?\n");
        printf("\n1. Nosta rahaa\n2. Laita rahaa\n3. Nayta tilin tiedot\n\n4. Lopetus\n\nValinta: ");

        scanf("%d",&valinta);
        lueRoskat();

        switch(valinta){

            case 1:
                TILIN_SALDO = nostaRahaa(TILIN_SALDO);
                break;

            case 2:
                TILIN_SALDO = laitaRahaa(TILIN_SALDO);
                break;

            case 3:
                tulostaTiedot(TILINUMERO_KOPIO, TILIN_SALDO);
                break;

            case 4:
                printf("\nKiitos kaynnista!\n");
                lopetus = 1;
                break;

            default:
                printf("\nVaarin meni! Yrit‰ uudelleen.\n");
                break;
        }
    }
    return 0;
}



/* tulostaTiedot - tulostaa k‰ytt‰j‰lle tilin tiedot.
 *
 * Parametrit:
 * - TILINUMERO_KOPIO[256] (char): pankkitilin tilinumeron kopio.
 * - TILIN_SALDO (double): pankkitilin saldo.
 * Ei palauta mit‰‰n.
*/
void tulostaTiedot(char TILINUMERO_KOPIO[256], double TILIN_SALDO){

    printf("\n--- TILISI TIEDOT: ---\n");
    printf("Tilinumero: %s\n", TILINUMERO_KOPIO);
    printf("Tilin saldo: %.2lf e\n", TILIN_SALDO);
    printf("----------------------\n");

}

/* nostaRahaa - kysyy k‰ytt‰j‰lt‰ noston m‰‰r‰n. M‰‰r‰n laillisuus
 * tarkistetaan. Jos nosto on laillinen, nosto suoritetaan ja
 * k‰ytt‰j‰lle tulostetaan kuinka monta 20e ja 50e seteli‰ h‰n sai.
 * Paluuarvona on tilin p‰ivitetty arvo.
 *
 * Parametrit:
 * - TILIN_SALDO (double): pankkitilin saldo, jota muokataan
 * k‰ytt‰j‰n noston m‰‰r‰n mukaisesti.
 *
 * Paluuarvo (double): TILIN_SALDO, p‰ivitetty tilin saldo noston
 * onnistuessa.
 *
*/
double nostaRahaa(double TILIN_SALDO){

    int NOSTON_MAARA;
    int SETELI_50_MAARA = 0;
    int SETELI_20_MAARA = 0;

    printf("\nPaljonko haluat nostaa rahaa?\n\nTilisi saldo on: %.2lf e\n\nNostoraja on 20-1000e.\n\nAnna noston maara tasalukuna: ",TILIN_SALDO);
    scanf("%d", &NOSTON_MAARA);

    if(NOSTON_MAARA % 10 != 0){
        printf("\nEt antanut tasalukua! Nosto epaonnistui.\n");
    }
    else {

        if(NOSTON_MAARA > 1000 || NOSTON_MAARA >= TILIN_SALDO){
            printf("\nYritit nostaa liian paljon rahaa.\n");
        }
        else if(NOSTON_MAARA < 20){
            printf("\nYritit nostaa liian vahan rahaa. Nosto epaonnistui.\n");
        }
        else {
            if (NOSTON_MAARA == 20){
                printf("\n1 kpl 20e seteli annettu.\n");
            }
            else if (NOSTON_MAARA == 40){
                printf("\n2 kpl 20e seteleita annettu.\n");
            }
            else if(NOSTON_MAARA == 50){
                printf("\n1 kpl 50e seteli annettu.\n");
            }
            else if(NOSTON_MAARA > 50){

                if (NOSTON_MAARA % 50 == 0){
                    SETELI_50_MAARA = NOSTON_MAARA / 50;
                    printf("\n%d kpl 50e seteleita annettu.\n", SETELI_50_MAARA);
                }
                else if ((NOSTON_MAARA % 50) == 20 || (NOSTON_MAARA % 50) == 40){
                    SETELI_50_MAARA = NOSTON_MAARA / 50;
                    SETELI_20_MAARA = (NOSTON_MAARA-(50*SETELI_50_MAARA)) / 20;
                    printf("\n%d kpl 50e seteleita annettu.", SETELI_50_MAARA);
                    printf("\n%d kpl 20e seteleita annettu.\n", SETELI_20_MAARA);
                }
                else {
                    SETELI_50_MAARA = (NOSTON_MAARA - 50) / 50;
                    SETELI_20_MAARA = (NOSTON_MAARA - (50*SETELI_50_MAARA)) / 20;
                    printf("\n%d kpl 50e seteleita annettu.", SETELI_50_MAARA);
                    printf("\n%d kpl 20e seteleita annettu.\n", SETELI_20_MAARA);
                }
            }
            TILIN_SALDO = TILIN_SALDO - NOSTON_MAARA;
        }
    }
    return TILIN_SALDO;
}


/* laitaRahaa - kysyy k‰ytt‰j‰lt‰ rahasumman, joka lis‰t‰‰n tilin saldoon
 * Tulostaa ruudulle ..
 * Paluuarvona on tilin uusi saldo.
 *
 * Parametrit:
 * - kysymys
 *
 * Paluuarvo (double): luku
 *
*/
double laitaRahaa(double TILIN_SALDO){

    double SUMMA;

    printf("\nPaljonko haluat laittaa tilillesi rahaa?\n\nAnna summa: ");
    scanf("%lf", &SUMMA);

    if(SUMMA <= 0){
        printf("\nEt antanut rahaa oikein!\nMuutoksia ei tehty.\n");
    }
    else{
        TILIN_SALDO = TILIN_SALDO + SUMMA;
    }
    return TILIN_SALDO;
}

/* lueRoskat - Poistaa rivinvaihdon tekstin per‰st‰.
 *
*/
void lueRoskat(void){
    while(fgetc(stdin) != '\n');
}
