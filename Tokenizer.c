#include "Tokenizer.h"

// heree
char sdbuff[1];
char tempo[250][20];
char red[50] = "";
int sizo = 0;
//hereee


//this is a method to remove extra spaces
char *RmSpaces(char *s)
{
	if (s == NULL)
	{
		return NULL;
	}
	int n = 0;
	int i = 0;
	for (i = 0; i < strlen(s); i++)
		if (s[i] == ' ' || s[i] == '\t')
		{
			continue;
		}
		else
			s[n++] = s[i];
	s[n] = '\0';
	return s;
}

//this is a method to remove a "\n" if there exists at the end of a string
char *choppy(char *s)
{
	char *n = malloc(strlen(s ? s : "\n"));
	if (s)
		strcpy(n, s);
	n[strlen(n) - 1] = '\0';
	return n;
}


//at the beginning of the project i didnt see the given classes so i ended up just having a merge of the 
// two classes which are toki and tokenizzer
int toki(FILE *fs)
{

	int fsrd;

	int i = 0;

	while ((fsrd = fread(sdbuff, sizeof(char), 1, fs)) > 0)
	{

		if (strcmp("", sdbuff) == 0)
		{
			continue;
		}

		if (strcmp("(", sdbuff) == 0 ||strcmp("%", sdbuff) == 0 || strcmp("+", sdbuff) == 0 || strcmp(" ", sdbuff) == 0 || strcmp("!", sdbuff) == 0 || strcmp(")", sdbuff) == 0 || strcmp("*", sdbuff) == 0 || strcmp("{", sdbuff) == 0 || strcmp(";", sdbuff) == 0 || strcmp("}", sdbuff) == 0 || strcmp(",", sdbuff) == 0 || strcmp("=", sdbuff) == 0)
		{


			strcpy(tempo[i], red);
			strcpy(tempo[i + 1], sdbuff);

			
			i += 2;
			memset(red, 0, sizeof(red));
		}
		else
		{
			if (strcmp("\n", sdbuff) == 0)
			{
				continue;
			}
			else
				strncat(red, sdbuff, 20);
		}

		if (strcmp("\n", sdbuff) == 0)
		{

			char *blue = choppy(red);
			strcpy(tempo[i], blue);
			i++;
			memset(red, 0, sizeof(red));
		}
	}
	strcpy(tempo[i], red);
	sizo = i;
	return 0;
}

//this method matches the tokens with the lexemes
int matchToke(struct lexics *aLex, int *numLex)
{

	int ko = 0;

	while (ko < sizo)
	{
		if (strcmp("(", aLex[ko].lexeme) == 0)
			aLex[ko].token = LEFT_PARENTHESIS;
		else if (strcmp(")", aLex[ko].lexeme) == 0)
			aLex[ko].token = RIGHT_PARENTHESIS;
		else if (strcmp("{", aLex[ko].lexeme) == 0)
			aLex[ko].token = LEFT_BRACKET;
		else if (strcmp("}", aLex[ko].lexeme) == 0)
			aLex[ko].token = RIGHT_BRACKET;
		else if (strcmp("while", aLex[ko].lexeme) == 0)
			aLex[ko].token = WHILE_KEYWORD;
		else if (strcmp("return", aLex[ko].lexeme) == 0)
			aLex[ko].token = RETURN_KEYWORD;
		else if (strcmp("=", aLex[ko].lexeme) == 0)
			aLex[ko].token = EQUAL;
		else if (strcmp(",", aLex[ko].lexeme) == 0)
			aLex[ko].token = COMMA;
		else if (strcmp(";", aLex[ko].lexeme) == 0)
			aLex[ko].token = EOL;
		else if (strcmp("*", aLex[ko].lexeme) == 0)
			aLex[ko].token = BINOP;
		else if (strcmp("==", aLex[ko].lexeme) == 0)
			aLex[ko].token = BINOP;
		else if (strcmp("!=", aLex[ko].lexeme) == 0)
			aLex[ko].token = BINOP;
		else if (strcmp("%", aLex[ko].lexeme) == 0)
			aLex[ko].token = BINOP;
		else if (strcmp("+", aLex[ko].lexeme) == 0)
			aLex[ko].token = BINOP;
		else if (strcmp("while", aLex[ko].lexeme) == 0)
			aLex[ko].token = WHILE_KEYWORD;
		else if (strcmp("void", aLex[ko].lexeme) == 0)
			aLex[ko].token = VARTYPE;
		else if (strcmp("", aLex[ko].lexeme) == 0)
		{
			ko++;
			continue;
		}

		else if (strcmp("int", aLex[ko].lexeme) == 0)
			aLex[ko].token = VARTYPE;
		else if ((validNumber(aLex[ko].lexeme)) == TRUE)
			aLex[ko].token = NUMBER;
		else if ((validIdentifier(aLex[ko].lexeme)) == TRUE)
			aLex[ko].token = IDENTIFIER;
		else
			return -1;

		(*numLex)++;

		ko++;
	}
	return 0;
}
// this is the tokenizer method given by the instructor
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf)
{

	toki(inf);

	int i = 0;
	int p = 0;

	while (p <= sizo)
	{
	
		char *pop = RmSpaces(tempo[p]);
		strcpy(tempo[p], pop);
		if (strcmp(" ", tempo[p]) == 0 || strcmp("", tempo[p]) == 0)
		{
			p++;
		}
		else
		{
			memset(&aLex[i], 0, sizeof(aLex[i]));

			strcpy(aLex[i].lexeme, tempo[p]);
			aLex[i].token = i;
			i++;
			p++;
		}
	}

	int kok = 0;
	int koke = 0;
	while (kok < i)
	{

		if (((strcmp("!", aLex[kok].lexeme) == 0) || (strcmp("=", aLex[kok].lexeme) == 0)) && (strcmp("=", aLex[kok + 1].lexeme) == 0))
		{
			strncat(aLex[kok].lexeme, aLex[kok + 1].lexeme, 20);
			koke++;
		}
		else
			strcpy(aLex[kok].lexeme, aLex[koke].lexeme);

		kok++;
		koke++;
	}
	int pik = matchToke(aLex, numLex);
	if (pik < 0)
		return FALSE;

	return TRUE;
}