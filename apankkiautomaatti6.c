#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int Saldofunktio(double saldo);
int Nostofunktio(double saldo);
double HaeSaldo(FILE *tilinumerotied, double *tilinsaldo);

int main(void){

    int toiminto=0;
    int tunnusluku;
    double tilinsaldo = 0;
    int oikeatunnusluku;
    char tilinumero[100];
    char account[] = ".acc";
    FILE *tilinumerotied;
    char line[128];

    printf("\ntervetuloa kayttamaan pankkiautomaattia\n\nSyota viisinumeroinen tilinumero\n");

    scanf("%s", tilinumero);

    strcat(tilinumero, account);

    while ( (tilinumerotied = fopen(tilinumero, "r")) == NULL)
    {
        printf("Tilinumero oli väärä, yritä uudelleen.\n");
        
        return 1;
    }

    fscanf(tilinumerotied, "%d", &oikeatunnusluku);

    printf("\nSyota nelinumeroinen tunnusluku(%d)\n", oikeatunnusluku);

    scanf("%d", &tunnusluku);

    fflush ( stdin );

    while (tunnusluku != oikeatunnusluku){

        fflush ( stdin );
        
        printf("\nSyottamasi luku ei ole Oikein, yrita uudelleen.\n");

        scanf("%s", tunnusluku);
    }

    HaeSaldo(tilinumerotied, &tilinsaldo);

    while (toiminto != 5){

        printf("\nOlet paavalikossa, syota haluamaasi toimintoa kuvaava numero; 1 Saldo, 2 Nosto, 3 Tapahtumat, 4 Liittyman lataus, 5 Lopeta\n");

        scanf("%d", &toiminto);

        fflush ( stdin );

        switch (toiminto){

            case 1:
            printf("Valitsit Saldo-toiminnon\n");
            Saldofunktio(tilinsaldo);
            break;

            case 2:
            printf("Valitsit Nosto-toiminnon\n");
            tilinsaldo = Nostofunktio(tilinsaldo);
            break;

            case 3:
            printf("Valitsit Tapahtumat-toiminnon\n");
            break;

            case 4:
            printf("Valitsit Liittyman lataus-toiminnon\n");
            break;

            case 5:
            printf("Valitsit Lopeta-toiminnon\n");
            break;
    
            default:
            printf("Vaara luku, valitse 1 ja 5 valilta.\n");
            break;
        }

    }
    printf("\nKiitos kaynnista!\n");

    fclose(tilinumerotied);

}

int Saldofunktio(double saldo){

    printf("Tilin saldo = %10.2lf\n", saldo);

    return(0);
}

double HaeSaldo(FILE *tilinumerotied, double *tilinsaldo){

    char line[128];
    fgets(line, sizeof line, tilinumerotied);

    fgets(line, sizeof line, tilinumerotied);
    *tilinsaldo = atof(line);

    return 0;
}

int Nostofunktio(double saldo){

    int nosto = 0;
    int toiminto;
    int maara50, maara20, jakojaannos;

    printf("Valitse haluamasi Nostosumma:\n1 20\n2 40\n3 50\n4 Valitse summa\n5 Lopeta\n");
    scanf("%d", &toiminto);

    switch (toiminto)
    {
    
        case 1:
            if (saldo > 20)
            {
                saldo = saldo - 20;
                printf("Uusi saldosi on %.2lf\n", saldo);
            }
            else
                printf("Kate ei riitä\n");
        break;

        case 2:
            if (saldo > 40)
            {
                saldo = saldo - 40;
                printf("Uusi saldosi on %.2lf\n", saldo);
            }
            else
                printf("Kate ei riitä\n");
        break;

        case 3:
            if (saldo > 50)
            {
                saldo = saldo - 50;
                printf("Uusi saldosi on %lf\n", saldo);
            }
            else
                printf("Kate ei riitä\n");
        break;

        case 4:
            printf("Syötä haluamasi noston suuruus:\n");
                
        
                    scanf("%d", &nosto);

                        if (nosto < 0)
                        {
                            printf("Et voi nostaa negatiivista summaa.\n");
                        }
                        

                        if (nosto > saldo)
                        {
                            printf("tililläsi ei riitä kate\n");
                        }

                        if (nosto % 10 != 0)
                        {
                            printf("Voit valita vain nollaan loppuvia lukuja.\n");
                        }
                        
                
                        if(nosto < saldo && nosto >= 40 && nosto % 10 == 0)
                        {
                            saldo = saldo - nosto;
                            maara50 = nosto / 50;
                            maara20 = (nosto % 50) / 20;
                            if (maara50 * 50 + maara20 * 20 == nosto)
                            {
                                printf("Nostit %d euroa muodossa %d viidenkymmenen euron seteliä ja %d kahdenkymmenen euron seteliä.\nUusi saldosi on %.2lf\n", nosto, maara50, maara20, saldo);
                            }
                            else
                            {
                                maara50 = maara50 - 1;
                                maara20 = (nosto - maara50 * 50) / 20;
                                printf("Nostit %d euroa muodossa %d viidenkymmenen euron seteliä ja %d kahdenkymmenen euron seteliä.\nUusi saldosi on %.2lf\n", nosto, maara50, maara20, saldo);
                            }
                            
                        }
        break;

        case 5:
            printf("Valitsit Lopeta-toiminnon\n");
        break;
    
        default:
            printf("Vaara luku, valitse 1 ja 5 valilta.\n");
        break;
    }

    return(saldo);
}