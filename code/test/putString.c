#include "syscall.h"

void print(){

    #if 1
    PutString("Bonjour, je suis trop long!");
    #endif
    
}


int main(){
    print();
}
