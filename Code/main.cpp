#include "function.h"

int main(){
    List* ls = createEmptyList();
    welcomePage();
    mainLogin(ls);
    delete ls;
    return 0;
}
