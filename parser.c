#include "Parser.h"
//this method to start off the class, checking that we used //all lexemes
_Bool parser(struct lexics *someLexics, int numberOfLexics)
{

	int j = 0;
	return function(&j, someLexics, numberOfLexics) && j == numberOfLexics;
}

//this method to gather the header and body if each are true //or false
_Bool function(int *j, struct lexics *someLexics, int numberOfLexics)
{
	if (header(j, someLexics, numberOfLexics) == FALSE)
	{
		return FALSE;
	}
	if (body(j, someLexics, numberOfLexics) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

//this method to check for the validity of the only the //header
_Bool header(int *j, struct lexics *someLexics, int numberOfLexics)
{
	if (someLexics[0].token == VARTYPE && someLexics[1].token == IDENTIFIER && someLexics[2].token == LEFT_PARENTHESIS)
	{
		*j = 3;
		if (someLexics[*j].token == VARTYPE)
			if (argdecl(j, someLexics, numberOfLexics) == FALSE)
			{
				return FALSE;
			}
		if (someLexics[*j].token == RIGHT_PARENTHESIS)
			(*j)++;
	}
	printf("I am finishing header\n");
	return TRUE;
}

//to check the validity of the argument declaration in the //header
_Bool argdecl(int *j, struct lexics *someLexics, int numberOfLexics)
{
	//VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
	int f = 0;
	if (someLexics[*j].token == VARTYPE)
	{
		(*j)++;
		if (someLexics[*j].token == IDENTIFIER)
		{
			(*j)++;

			while (someLexics[*j].token == COMMA)
			{

				(*j)++;
				if (someLexics[*j].token == VARTYPE)
				{

					(*j)++;
				}

				if (someLexics[*j].token == IDENTIFIER)
				{

					(*j)++;
				}
			}
		}
	}
	return TRUE;
}


//to check the body validity of the code
_Bool body(int *j, struct lexics *someLexics, int numberOfLexics)
{

	if (someLexics[*j].token == LEFT_BRACKET)
	{
		(*j)++;
		if (someLexics[*j].token != RIGHT_BRACKET)
		{
			if (statementlist(j, someLexics, numberOfLexics) == FALSE)
				return FALSE;
		}
		if (someLexics[*j].token == RIGHT_BRACKET)
		{
			(*j)++;
		}
	}
	printf("I am finishing body\n");
	return TRUE;
}
// this is what constructs the body other than the brackets
_Bool statementlist(int *j, struct lexics *someLexics, int numberOfLexics)
{	
	if (statement(j, someLexics, numberOfLexics) == FALSE)
	{
		return FALSE;
	}
	while (*j<numberOfLexics&&someLexics[*j].token != RIGHT_BRACKET){

		if (statement(j, someLexics, numberOfLexics) == FALSE)
		{
			return FALSE;
		}}
	if (someLexics[*j].token == RIGHT_BRACKET)
		(*j)++;

	return TRUE;
}
// to check what type of statement we are dealing with and //expands on that specifically
_Bool statement(int *j, struct lexics *someLexics, int numberOfLexics)
{

	if (someLexics[*j].token == WHILE_KEYWORD)
		return whileloop(j, someLexics, numberOfLexics);
	else if (someLexics[*j].token == RETURN_KEYWORD)
		return returno(j, someLexics, numberOfLexics);
	else if (someLexics[*j].token == IDENTIFIER)
		return assignment(j, someLexics, numberOfLexics);
	else if (someLexics[*j].token == LEFT_BRACKET)
		return body(j, someLexics, numberOfLexics);

	else
		return FALSE;
}

//expanding on the assignment statement and checking if we //are assigning values to identifiers
_Bool assignment(int *j, struct lexics *someLexics, int numberOfLexics)
{
	//IDENTIFIER EQUAL expression EOL
	if (someLexics[*j].token == IDENTIFIER)
	{
		(*j)++;

		if (someLexics[*j].token == EQUAL)
		{
			(*j)++;
			if (expression(j, someLexics, numberOfLexics) == FALSE)
			{
				return FALSE;
			}
			if (someLexics[*j].token != EOL)
			{
				return FALSE;
			}
			if (someLexics[*j].token == EOL)
			{
				(*j)++;
			}
		}
	}
	return TRUE;
}

//checks for the return statement returno cuz return is //already defined and expands on it
_Bool returno(int *j, struct lexics *someLexics, int numberOfLexics)
{
	//RETURN_KEYWORD expression EOL
	if (someLexics[*j].token == RETURN_KEYWORD)
	{
		(*j)++;
	}
	if (expression(j, someLexics, numberOfLexics) == FALSE)
	{
		return FALSE;
	}
	if (someLexics[*j].token != EOL)
	{
		return FALSE;
	}
	if (someLexics[*j].token == EOL)
	{
		(*j)++;
	}
	return TRUE;
}

//checks the validity if the while loop structure and checks //it different components
_Bool whileloop(int *j, struct lexics *someLexics, int numberOfLexics)
{
	//--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
	if (someLexics[*j].token == WHILE_KEYWORD)
	{
		(*j)++;
	}
	if (someLexics[*j].token == LEFT_PARENTHESIS)
	{
		(*j)++;
	}
	if (expression(j, someLexics, numberOfLexics) == FALSE)
	{
		return FALSE;
	}
	if (someLexics[*j].token == RIGHT_PARENTHESIS)
	{
		(*j)++;
	}
	if (statement(j, someLexics, numberOfLexics) == FALSE){
		 return FALSE;}

	return TRUE;
}

//checks the different expressions and their validity
// in this case there are two types which are expressed by //the  two if statements
_Bool expression(int *j, struct lexics *someLexics, int numberOfLexics)
{
	//--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS

	if (someLexics[*j].token == LEFT_PARENTHESIS)
	{	
		(*j)++;
		if (expression(j, someLexics, numberOfLexics) == FALSE){
			return FALSE;}
		if (someLexics[*j].token == RIGHT_PARENTHESIS)
			(*j)++;
		
		return TRUE;
	}

	else if (someLexics[*j].token == IDENTIFIER || someLexics[*j].token == NUMBER)
	{	
		(*j)++;
		while (someLexics[*j].token == BINOP)
		{
			(*j)++;
			if (someLexics[*j].token == IDENTIFIER || someLexics[*j].token == NUMBER)
				(*j)++;
		}
		return TRUE;
	}
	return FALSE;
}

// int term(int index, struct lexics *someLexics, int numberOfLexics)
// {
// 	if (someLexics[index].token == IDENTIFIER || someLexics[index].token == NUMBER)
// 		return 1;
// 	else
// 		return -1;
// }