#include "syscall.h"

void wow(int c){
    PutChar(c);
    ThreadExit();
}

void tcho(int i){
    for(i; i<10; i++){
        PutChar('a');
    }
    PutChar('\n');
    ThreadExit();
}

int main(){

    volatile int i = 0;
    int j = 0;

    for(j; j<7; j++){
        ThreadCreate(tcho, i);
        ThreadExit();
    }
}
