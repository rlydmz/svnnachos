#include "pageprovider.h"
#include "system.h"

PageProvider::PageProvider(int numPages){
    map = new BitMap(numPages);
}

PageProvider::~PageProvider(){
    delete map;
}

int PageProvider::GetEmptyPage(){
    int tmp = map->Find();
    memset(&machine->mainMemory[PageSize*tmp],0,sizeof(PageSize));
    return tmp;
}
        
void PageProvider::ReleasePage(int index){
    map->Clear(index);
}
        
int PageProvider::NumAvailPage(){
    return map->NumClear();
}