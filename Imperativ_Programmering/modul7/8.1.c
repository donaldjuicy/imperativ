/*
=========================================================
FORMÅL:
Programmet genererer 25 tilfældige menukombinationer
med forret, hovedret og dessert, og anvender funktionspointere
til at konvertere enum-værdier til tekst.

FAGORD:
- Enum: Enumeration type, definerer et sæt navngivne heltalsværdier
- Funktionspointer: Pointer til en funktion
- Rand: Funktion der genererer pseudo-tilfældige tal
- srand: Initialiserer tilfældigheds-generator med seed
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//==========================================================
// ENUMERATIONER
//==========================================================
typedef enum {
    guacamole,
    tarteletter,
    lakserulle,
    graeskarsuppe,
    FORRET_MAX
} Forret;

typedef enum {
    gyldenkaal,
    hakkeboef,
    gullash,
    forloren_hare,
    HOVEDRET_MAX
} Hovedret;

typedef enum {
    pandekager_med_is,
    gulerodskage,
    choklademousse,
    citronfromage,
    DESSERT_MAX
} Dessert;

//==========================================================
// FUNKTIONER: konverter enum til tekst
//==========================================================
const char* forret_to_string(Forret f)
{
    switch(f)
    {
        case guacamole: return "Guacamole";
        case tarteletter: return "Tarteletter";
        case lakserulle: return "Lakserulle";
        case graeskarsuppe: return "Graeskarsuppe";
        default: return "Ukendt forret";
    }
}

const char* hovedret_to_string(Hovedret h)
{
    switch(h)
    {
        case gyldenkaal: return "Gyldenkaal";
        case hakkeboef: return "Hakkeboef";
        case gullash: return "Gullash";
        case forloren_hare: return "Forloren hare";
        default: return "Ukendt hovedret";
    }
}

const char* dessert_to_string(Dessert d)
{
    switch(d)
    {
        case pandekager_med_is: return "Pandekager med is";
        case gulerodskage: return "Gulerodskage";
        case choklademousse: return "Choklademousse";
        case citronfromage: return "Citronfromage";
        default: return "Ukendt dessert";
    }
}

//==========================================================
// FUNKTION: maaltid
// Tilfældig kombination ved hjælp af funktionspointere
//==========================================================
void maaltid(const char* (*f_forret)(Forret),
             const char* (*f_hovedret)(Hovedret),
             const char* (*f_dessert)(Dessert))
{
    // Tilfældige enum-værdier
    Forret f = (Forret)(rand() % FORRET_MAX);
    Hovedret h = (Hovedret)(rand() % HOVEDRET_MAX);
    Dessert d = (Dessert)(rand() % DESSERT_MAX);

    // Udskriv kombinationen via funktionspointere
    printf("%-15s | %-15s | %-15s\n",
           f_forret(f),
           f_hovedret(h),
           f_dessert(d));
}

//==========================================================
// MAIN: genererer menukort med 25 kombinationer
//==========================================================
int main(void)
{
    srand(time(NULL)); // seed for rand

    printf("Tilfaeldigt menukort med 25 kombinationer:\n");
    printf("Forret          | Hovedret        | Dessert        \n");
    printf("---------------------------------------------------\n");

    for(int i = 0; i < 25; i++)
    {
        // Kald maaltid med funktionspointere
        maaltid(forret_to_string, hovedret_to_string, dessert_to_string);
    }

    /*
    EKSEMPEL PÅ OUTPUT (tilfældigt):

    Tilfaeldigt menukort med 25 kombinationer:
    Forret          | Hovedret        | Dessert        
    ---------------------------------------------------
    Guacamole       | Hakkeboef       | Gulerodskage   
    Lakserulle      | Gullash         | Citronfromage  
    Tarteletter     | Gyldenkaal      | Pandekager med is
    Graeskarsuppe   | Forloren hare   | Choklademousse
    ...
    */

    return 0;
}
