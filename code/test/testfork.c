#include "syscall.h"

int main(){
    ForkExec("test/putchar");
    ForkExec("test/putchar");
}