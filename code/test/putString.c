#include "syscall.h"

void print(){

    #if 1
    PutString("Bonjour !");
    #endif
    
}


int main(){
    print();
    Halt();
}
