#include <stdio.h>          // printf()
#include <stdlib.h>         // free()
#include <string.h>         // strcpy(), memset()
#include "gimme_mem.h"      // gimme_mem_malloc()

#define BUF_SIZE 64


int main(void)
{
    /***********************************************************/
    /* 4. Invalid Memory Access                                */
    /***********************************************************/
    // LOCAL VARIABLES
    char *bufInvAccess = (char *)gimme_mem_malloc((BUF_SIZE * sizeof(char)) + 1);

    // COPY
    strcpy(bufInvAccess, "Hello World!\n");

    // PRINT
    printf("%s", bufInvAccess);

    // CLEAN UP
    free(bufInvAccess);
    memset(bufInvAccess, 0x0, (BUF_SIZE * sizeof(char)) + 1);

    // DONE
    return 0;
}
