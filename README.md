# c-tokenizer-and-recursive-descent-parser
This program consists of four class files: Givens.c Tokenizer.c Parser.c and Analyzer.c . Each class
file has a corresponding header file where all constants, method declarations, struct definitions, include
statements, and global variables will be placed. (Header files are named the same as their corresponding class
file but with a .h file extension rather than a .c file extension).

## Givens.c
Givens.c includes constants for TRUE and FALSE, constants for all token values in the given lexical structure, a constant for the max size of a lexeme, and the definition for a struct named lexics, which consists an int property named token and a character array property named lexeme. The lexics struct is used to store both a token and its corresponding lexeme. Givens.c also provides two functions
which return a boolean value indicating if the given String matches a specified regular expression.

## Tokenizer.c 
this class will read characters from a given FILE variable and convert them into tokens. creating lexemes and the associated tokens. Each time a lexeme is generated, a new lexics struct will be created and the lexeme added. The generated lexeme is then tokenized, the token is added to the generated lexics struct, the lexics struct is then added to the end of the given lexics array. 

the tokenizing method should return TRUE if the tokenization process is finished, and if an error occurs throughout the process it will return FALSE.

## Parser.c (recursive descent parser with single symbol lookahead)
the core implementation of the recursive descent parser will take place in this class and the parsing will be based on the EBNF grammar included in the repository. the parsing method takes an array of type lexics and an int pointer representing the number of tokens in the given lexics array. The parser method must take the given array of lexics structs and determine if it is legal in the language
defined by the given grammar. The purpose of our parser is to apply the grammar rules and report any syntax
errors. If no syntax errors are identified, parser returns TRUE, otherwise it returns FALSE.


## Analyzer.c
this class includes a method to prompt the user for a file path, it also initializes an array of type lexics and an int containing the number of lexics in the array (initialized to 0). Analyzer.c makes calls both the tokenizer method and the parser method, passing the initialized int an array to both functions. 



