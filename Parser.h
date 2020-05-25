#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Givens.h"

_Bool parser(struct lexics *someLexics, int numberOfLexics);
_Bool function(int *j,struct lexics *someLexics, int numberOfLexics);
_Bool header(int *j,struct lexics *someLexics, int numberOfLexics);
_Bool argdecl(int *j,struct lexics *someLexics, int numberOfLexics);
_Bool body(int*j,struct lexics *someLexics, int numberOfLexics);
_Bool statementlist(int*j,struct lexics *someLexics, int numberOfLexics);
_Bool statement(int*j,struct lexics *someLexics, int numberOfLexics);
_Bool assignment(int*j,struct lexics *someLexics, int numberOfLexics);
_Bool returno(int*j,struct lexics *someLexics, int numberOfLexics);
_Bool whileloop (int*j,struct lexics *someLexics, int numberOfLexics);
_Bool expression(int*j,struct lexics *someLexics, int numberOfLexics);