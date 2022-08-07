//
// Created by MSI on 7/25/2022.
//

#include "uart_lib.h"

int main() {

    printf("UART MONITOR\n");
    char  dt[]="COM1";

    int st = init(9600,dt,10,10);
    int sx=init(9600,dt,10,10);

    printf("st=%d\nError msg=%s\n",st,errormsg);
    writeuart("at");
    char * p;
    int x=0;
   // while (1){
        p=readu();
            //printf(":%s:",p);
        //p=readuart();
        printf("[%s]",p);
        sleep(1);
        x++;
  //  }

    closeuart(hserial);
    closeuart(hserial);
    printf("END");
    return 0;
}
