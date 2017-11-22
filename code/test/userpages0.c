#include "syscall.h"

void tcho(int i){
    for(i; i<5; i++){
        PutChar('o');
    }
}

int main(){
    //PutString("Ca marche pour sur");

    int i=0;

    ThreadCreate(tcho, i);
    ThreadExit();

}