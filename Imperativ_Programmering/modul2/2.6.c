//Kode 1
#include <stdio.h>

int main(void) {
    int c1, c2;
int scanRes;

/* %c springer IKKE whitespace over */
scanRes = scanf("%c%c", &c1, &c2);

/*
Input: "a b"
c1 = 'a'
c2 = ' '   (mellemrum!)
scanRes = 2  (to succesfulde læsninger)
*/

return 0;
}




//Kode 2

#include <stdio.h>

int main(void){
    int i1, i2;
int scanRes;

/* %d ignorerer whitespace og kræver gyldige tal */
scanRes = scanf("%d%d", &i1, &i2);

/*
Input: "123.456"
i1 = 123
scanf stopper ved '.'
scanRes = 1  (kun ét heltal læst)
*/

return 0;
}
