#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Givens.h"


char *RmSpaces(char * s);
char *choppy( char *s );
int toki(FILE * fs);
int matchToke(struct lexics *aLex, int *numLex);
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE * inf);
