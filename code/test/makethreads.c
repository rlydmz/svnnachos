#include "syscall.h"

void wow(int c){
    PutChar(c);
    ThreadExit();
}

int main(){
    ThreadCreate(wow, 'c');
    ThreadExit();
}
