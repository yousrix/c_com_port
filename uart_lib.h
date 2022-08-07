//
// Created by MSI on 7/25/2022.
//

#ifndef CUART_UART_LIB_H
#define CUART_UART_LIB_H
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int init(int baud,char * com,int rwt, int lng);
int writeuart(char*data);
char *readuart ();
int closeuart();
char* readu();
char * geterror();
extern char *errormsg;
extern HANDLE hserial;
#endif //CUART_UART_LIB_H
