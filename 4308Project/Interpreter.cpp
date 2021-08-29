#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Global variables and constants
char nextChar;
int charClass;
char lexeme[100];
int varCount;
int nextToken;
int lexCounter;
int currentVariable;
int left_op;
int right_op;
int numOfOperands = 1;
int mathOp;
int result;
string tempName;
string comparisonName;

//lexer functions
int lexer();
void getChar();
void getNonBlank();

//parser functions
void stmt_list();
void stmt();
void flow_ctrl_stmt();
void factor();
void expr();
void term();
void declaration_stmt();
void assignment_stmt();
void bool_expr();	


ifstream inputFile("inputFile.txt");

//Character classes
#define LETTER 0
#define DIGIT 1
#define OTHER 99
#define EOF -1

//Token codes
#define IDENTIFIER 2
#define INTEGER    3
#define L_PAREN    4
#define R_PAREN    5
#define ASSIGN_OP  6	
#define GRTR_COMP  7
#define LSSR_COMP  8
#define GE_COMP    9
#define LE_COMP    10
#define EQ_COMP    11
#define SEMI_COLON 13
#define SUB_OP     14
#define ADD_OP     15
#define MULT_OP    16
#define DIV_OP     17
#define L_BRCE    18
#define R_BRCE    19
#define DECLARATION   20 //corresponds to lexeme "var"
#define WHILE      21
#define IF         22


//holds the name and value of a variable defined in the code
class symbolTable {
	public:
		string name;
		int value;
};

symbolTable variables[3];


int main() {
    if (!inputFile.is_open()) {
        cout << "file not found." << endl;
	} 
    else {
		getChar();
		lexer();
		stmt_list(); //start program
	}
	inputFile.close();
    return 0;
}

/*
	Adds characters to the current lexeme being immediately tokenized
*/
void addChar() {
	lexeme[lexCounter++] = nextChar;
	lexeme[lexCounter] = 0;
}

/*
	A lookup table to identify non-alphanumeric characters
*/
int  lookup(char  ch) {
	/*
		If currentChar is a comparison operator, check the following char for another
		comparison operator, if it is then the comparison operator is a two-piece comparison
		operator. Otherwise, the comparison operator is a one-piece comparison operator.
	*/

	if (ch == '=') {
		addChar();
		getChar();
		if (nextChar == '=') {
			addChar();
			getChar();
			return nextToken = EQ_COMP;
		}
		return nextToken = ASSIGN_OP;
	} else if(ch == '>'){
		addChar();
		getChar();
		if (nextChar == '=') {
			addChar();
			getChar();
			return nextToken = GE_COMP;
		}
		return nextToken = GRTR_COMP;
	} else if(ch == '<'){
		addChar();
		getChar();
		if (nextChar == '=') {
			addChar();
			getChar();
			return nextToken = LE_COMP;
		}
		return nextToken = LSSR_COMP;
	}

	
	switch (ch) {
		case  '(':
			addChar();
			nextToken = L_PAREN;
			break;
		case  ')':
			addChar();
			nextToken = R_PAREN;
			break;
		case  '+':
			addChar();
			nextToken = ADD_OP;
			break;
		case  '-':
			addChar();
			nextToken = SUB_OP;
			break;
		case  '*':
			addChar();
			nextToken = MULT_OP;
			break;
		case  '/':
			addChar();
			nextToken = DIV_OP;
			break;
		case '>':
			addChar();
			nextToken = GRTR_COMP;
			break;
		case '<':
			addChar();
			nextToken = LSSR_COMP;
			break;
		case ';':
			addChar();
			nextToken = SEMI_COLON;
			break;
		case '{':
			addChar();
			nextToken = L_BRCE;
			break;
		case '}':
			addChar();
			nextToken = R_BRCE;
			break;
	default:      addChar();      nextToken = EOF;      break;
	}  
	getChar();
	return  nextToken;
}



/*
	geChar()
	Retrieves the next character in an input file and identifies the class of the character 
	(EOF, LETTER, DIGIT, OTHER)
*/
void getChar() {
	
	inputFile.get(nextChar);
	
	
	if (nextChar != EOF) {
		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else  charClass = OTHER;
	}
	else     charClass = EOF;
}

/*
	getNonBlank()
	Trims and discards white space in an input file until it obtains a character
*/
void getNonBlank() {
	while (isspace(nextChar) && nextToken != EOF)
		getChar(); 
}

//lexical analyzer function
int lexer() {
	lexCounter = 0;
	getNonBlank();
	
	switch (charClass) {

			/* Parse identifiers */
		case  LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();        
				getChar();
				if (lexeme[0] == 'v' && lexeme[1] == 'a' && lexeme[2] == 'r') {
					nextToken = DECLARATION;
					printf("\nNext token is: %d, Next lexeme is %s\n", nextToken, lexeme);
					return nextToken;
				}
				else if (lexeme[0] == 'i' && lexeme[1] == 'f') {
					nextToken = IF;
					printf("\nNext token is: %d, Next lexeme is %s\n", nextToken, lexeme);
					return nextToken;
				}
				else if (lexeme[0] == 'E' && lexeme[1] == 'O' && lexeme[2] == 'F') {
					nextToken = EOF;
					printf("\nNext token is: %d, Next lexeme is %s\n", nextToken, lexeme);
					return nextToken;
				}
				else if (lexeme[0] == 'w' && lexeme[1] == 'h' && lexeme[2] == 'i' && lexeme[3] == 'l' && lexeme[4] == 'e') {
					nextToken = WHILE;
					printf("\nNext token is: %d, Next lexeme is %s\n", nextToken, lexeme);
					return nextToken;
				}
			}    nextToken = IDENTIFIER;
			break;
			/* Parse integer literals */
		case  DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = INTEGER;
			break;
			/* Parentheses and operators */
		case  OTHER:
			lookup(nextChar);
			break;
			/* EOF */
		case  EOF:      nextToken = EOF;
			
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;       break;

		} /* End of switch */
		printf("\nNext token is: %d, Next lexeme is %s\n", nextToken, lexeme);
		return  nextToken;
	}  
    
    





/*****************************************************/
/* stmt_list
 Grammar rule: <stmt_list> -> <stmt> {<stmt>}
 */
void stmt_list() {
	printf("Enter <stmt_list>\n");
	do {
		stmt();
		lexer(); 
	} while (nextToken != EOF);
	printf("exit <stmt_list>\n");
	
};

/*****************************************************/
/* stmt
Grammar rule: <stmt> -> <assignment> | <flow_ctrl_stmt> | <declaration>
*/
void stmt() {
	printf("Enter <stmt>\n");
	
	if (nextToken == IDENTIFIER){
		//A statement that begins with an identifier must be an assignment statement
		assignment_stmt();
	}
	else if (nextToken == IF || nextToken == WHILE) {
		flow_ctrl_stmt();
	}
	else { 
		declaration_stmt();
	}
	printf("exit <stmt>\n");
};

/*****************************************************/
/* flow_ctrl_stmt
 Grammar rule: <flow_ctrl_stmt> -> ( if | while) ( <bool_expr> ) <stmt_list> 
 */
void flow_ctrl_stmt() {
	printf("<flow_ctrl_stmt>\n");
	lexer(); //Tokenizing "("
	lexer(); //tokenize the next expr

	bool_expr();
	lexer(); //Tokenize "{"
	lexer(); //tokenize next stmt or expr
	stmt();
		
	lexer(); //Tokenize "}"
	printf("exit <flow_ctrl_stmt>\n");
};

/*	assignment_stmt()
	Grammar rule: <assignment_stmt> -> <factor> = <expr>; 
*/
void assignment_stmt() {
	printf("<assignment>\n");
	comparisonName = "";
	/*comparisonName and its use in the following for and while, allows a recently retrieved identifier to be compared against 
	  a list of existing variable names that have been previously declared
	*/
	
	int j = 0;
	while (lexeme[j] != '\0') {
		comparisonName += lexeme[j];
		j++;
	}

	for (int i = 0; i < 9; i++) {
		if (variables[i].name == comparisonName) {
			currentVariable = i;
			break;
		}
	}
	
	factor(); 
	lexer();
	expr();
	variables[currentVariable].value = result;
	
	left_op = 0; right_op = 0; result = 0;
	printf("exit <assignment>\n");
}

/*  declaration_stmt
	Grammar rule: declaration_stmt -> var <factor> = <expr>
*/
void declaration_stmt() {
	printf("<declaration>\n");
	lexer(); //tokenizes identifier
	
	//make a new variable with the name obtained from lexing.
	
	int step = 0;
	while (lexeme[step] != '\0') {
		tempName += lexeme[step];
		step++;
	}
	variables[varCount].name = tempName;
	varCount++;
	tempName = "";
	assignment_stmt();
	printf("exit <declaration>\n");
	


}

/* bool_expr
   Grammar rule: <bool_expr> -> <expr> comparison_operator <expr>
 */
void bool_expr() { 
	printf("<bool_expr>\n");
	expr(); 
	
	lexer();
	
	expr(); //will parse the expression and tokenize the closing ")"
	printf("exit <bool_expr>\n");
}

/*****************************************************/
/* expr
Grammar rule: <expr> -> <term> {(+ | -) <term>}
*/
void expr() {
	printf("Enter <expr>\n");
	/* Parse the first term */
	int tempOp;
	int tempVal;
	term();
	tempVal = left_op;
	/* As long as the next token is + or -, get
	the next token and parse the next term */
	while (nextToken == ADD_OP || nextToken == SUB_OP) {
		numOfOperands = 2;
		tempOp = nextToken;
				
		lexer();
		term();
		if (tempOp == ADD_OP)
			tempVal += right_op;
		else if (tempOp == SUB_OP)
			tempVal -= right_op;

		
	}
	result = tempVal;
	
	printf("Exit <expr>\n");
}	

/*****************************************************/
/* term
Parses strings in the language generated by the rule:
<term> -> <factor> {(* | /) <factor>)
*/
void term() {
	printf("<term>\n");
	/* Parse the first factor */
	factor();
	/* As long as the next token is * or /, get the
	next token and parse the next factor */
	while (nextToken == MULT_OP || nextToken == DIV_OP) {
		numOfOperands = 2;
		mathOp = nextToken;
		lexer();
		factor();
		if (mathOp == MULT_OP)
			right_op = left_op * right_op;
		else if (mathOp == DIV_OP)
			right_op = left_op / right_op;
	}
	printf("Exit <term>\n");
} /* End of function term */

  /*****************************************************/
/* factor
Parses strings in the language generated by the rule:
<factor> -> id | int_constant | ( <expr> )
*/
void factor() {
		printf("<factor>\n");
		
	/* Determine which RHS */
	if (nextToken == IDENTIFIER || nextToken == INTEGER) {
		/* Get the next token */
		
		if (nextToken == INTEGER) {
			string tempInt;
			for (int i = 0; i < 50; i++) {
				if (lexeme[i] == '\0')
					break;

				tempInt += lexeme[i];
			}
			if (numOfOperands == 1) {
				left_op = stoi(tempInt);
				
			}
			else if (numOfOperands == 2) {
				right_op = stoi(tempInt);
				numOfOperands = 1;
				
			}
		}
		else if (nextToken == IDENTIFIER) {
			comparisonName = "";
			int j = 0;
			while (lexeme[j] != '\0') {
				comparisonName += lexeme[j];
				j++;
			}

			for (int i = 0; i < 9; i++) {
				if (variables[i].name == comparisonName) {
					currentVariable = i;
					break;
				}
				
			}
			if (numOfOperands == 1) {
				left_op = variables[currentVariable].value;
				
			}
			else if (numOfOperands == 2) {
				right_op = variables[currentVariable].value;
				numOfOperands = 1;
				
			}
		}
		lexer();
	}
	/* If the RHS is ( <expr> ), call lex to pass over the
	left parenthesis, call expr, and check for the right
	parenthesis */
	else if (nextToken == L_PAREN) {
		 	lexer();
			expr();
			if (nextToken == R_PAREN)
				lexer();
	}

	printf("Exit <factor>\n");;
}
