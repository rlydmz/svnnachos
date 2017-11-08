#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *lock;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }

static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

SynchConsole::SynchConsole(const char *in, const char *out)
{
readAvail = new Semaphore("read avail", 0);
writeDone = new Semaphore("write done", 0);
lock = new Semaphore("lock done", 1);
console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole()
{
delete console;
delete writeDone;
delete readAvail;
}

void SynchConsole::SynchPutChar(int ch)
{
  lock->P();
  console->PutChar (ch);
  writeDone->P ();
  lock->V();
}

int SynchConsole::SynchGetChar()
{
  lock->P();
  readAvail->P ();
  char c = console->GetChar();
  lock->V();
  return c;
} 

void SynchConsole::SynchPutString(const char s[])
{
  if(s != NULL){
    int i = 0;
    while(s[i] != '\0'){
      SynchPutChar(s[i]); 
      i++;
    }
  }
  else{
    fprintf(stderr, "Chaine vide");
  }
}

void SynchConsole::SynchGetString(char *s, int n)
{
  if (s != NULL)
  {
    char ch = 0;
    for (int i = 0; i < n; i++)
    {
      ch = SynchGetChar();
      if (ch == '\0' || ch == '\n')
      {
        s[i] = '\0';
        break;
      }
      else if (i == n - 1)
      {
        s[i] = '\0';
        break;
      }
      else
        s[i] = ch;
    }
  }
}

int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size){
  int tmp = 0;
  for(unsigned i=0; i<size; i++){
    machine->ReadMem(from+i, 1, &tmp); 
    if((char)tmp != '\0'){
      to[i] = (char)tmp;
    } 
    else{
      to[i] = '\0';
      return i+1;
    } 
  }
  //to[size-1] = '\0';
  return size;
}

int SynchConsole::copyStringToMachine(int to, char *from, unsigned size){

  for(unsigned i=0; i<size; i++){
      machine->WriteMem(to+i, 1, from[i]); 
      if(from[i] == '\0')
        return i;
  }
  machine->WriteMem(to + size-1, 1, '\0');
  return size;

}  


#endif // CHANGED
