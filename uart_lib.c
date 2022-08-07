

#include "uart_lib.h"
 char *errormsg;
 HANDLE hserial;
 int ln=1;
/**
 *
 * @param baud rate
 * @param com name
 * @param rwt timeout r/w
 * @return
 */
 static int inisalized=0;
int init(int baud,char * com,int rwt,int lng)
{
    if(inisalized){ errormsg="inisialized";return 0;}
    ln=lng;
    hserial=CreateFileA(com,
                       GENERIC_WRITE|GENERIC_READ,
                       0,0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0);
    if(hserial==INVALID_HANDLE_VALUE)
    {

        if(GetLastError()==ERROR_FILE_NOT_FOUND )
        {
            errormsg="Porte not connected";
            inisalized=0;
            printf("\n Porte not connected\n");
            return -1;
        }
        else
        {
            printf("port locked\n");
            errormsg="port locked";
            inisalized=0;
            return -1;
        }
    }
    else
    {
       printf("connected\n");
        errormsg="connected";
    }

    DCB dcbparam={0};

    COMMTIMEOUTS timeout={0};
    if(!GetCommState(hserial,&dcbparam)){
        printf("error get state\n");
        errormsg="error get param";
        inisalized=0;
        return -1;
    }else{
       printf("baud=%d\nbyteSize=%d\n",dcbparam.BaudRate,dcbparam.ByteSize);
        timeout.ReadIntervalTimeout=rwt;
        timeout.WriteTotalTimeoutConstant=rwt;
        timeout.ReadTotalTimeoutConstant=rwt;

        SetCommTimeouts(hserial,&timeout);
        //GetCommTimeouts(hserial,&timeout);
    }
    dcbparam.BaudRate=CBR_9600;

    if(!SetCommState(hserial,&dcbparam)){
        printf("error set param %d\n :%d:\n",baud,GetLastError());
        errormsg="error set param";
        inisalized=0;
        return -1;
    }
    printf("\ner::%s\n",errormsg);
    inisalized=1;

    return 1;
}
/**
 *
 * @param data output buffer
 * @return
 */
int writeuart(char*data){

    DWORD writed=0;
    if (!WriteFile(hserial,data,strlen(data),&writed,NULL))
    {
        //printf("ERROR writing\n");
        errormsg="ERROR writing";
        return -1;
    }else{
       // printf("writed=%d\n",writed);
        return 0;
    }
}
/**
 *
 * @param data input buffer
 * @return 0
 */
 /*
 char * readuart()
 {
     DWORD readed=0;
     char buffer[100];
     if(!ReadFile(hserial,buffer,100,&readed,NULL))
     {
         printf("ERROR reading{%d}{%d}\n",readed,GetLastError());
         errormsg="ERROR reading";
         return "-1";
     }
     else{
         printf(":%s:",buffer);
         return buffer;
     }
 }

*/

 /***
  * get last error
  * @return error as string
  */
  char* geterror(){
      return errormsg;
 }
static char data[100];

char* readu()
{
        //   printf("rin\n");
    DWORD i=0;
    memset(data,0,ln);
    if(!ReadFile(hserial, data, ln, &i, NULL))
    {
       // printf("ERROR reading{%d}{%d}[%s]\n", i, GetLastError(), data);
        errormsg="ERROR reading";
        printf("rout\n");

        return "";
    }
    else{
         //printf("\nreceived<%s>{%d}",data,i);
     //   printf("rout\n");
        return data;
    }


}
int closeuart()
{
   if(!CloseHandle(hserial))
   { printf("error closing");return 0;}else{inisalized=0;errormsg="";return 1;}
}