%{
    #include<stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "flatner/flatner.h"
    #include "flatner/expression.h"

    extern FILE * yyin;
    extern char *outputFileName;
    int yylex();
    void yyerror(char*);
%}


%token <s> INT FLOAT BOOL NUMBER LABEL ASG TERMINATOR  IF WHILE LCURL RCURL  LPAREN RPAREN LE ME LT MT EQ NE PLUS MINUS MUL DIV AND OR NOT PRINT STRING COMMA

%type <s> type cmp logicB term factor

%union{
    char * s;
}
%start stmts


%%

stmts: stmt stmts
    |
    ;

stmt: decl | assign | loop | cond | print

decl: type LABEL TERMINATOR  {addDeclareInstruction(typeStringToint($1), $2);};

assign:  LABEL {setIndentifier($1);}ASG {expressionStart();} expr {expressionEnd(INITIALIZE);}TERMINATOR ;

expr : d 
    | expr logicB  d             {pushExpTree($2);}
    ;

d : c
    | NOT  d             {pushExpTree($1);}
    ;

c: aexpr
    |  aexpr cmp  c                  {pushExpTree($2);}
    ;
aexpr: term
    | term PLUS aexpr                {pushExpTree($2);}
    |  term MINUS  aexpr          {pushExpTree($2);}
    ;

term: factor
    |  factor MUL term     {pushExpTree($2);}
    | factor DIV term        {pushExpTree($2);}
    ;

factor: NUMBER      {pushExpTree($1);}
    | LABEL  {pushExpTree($1);}
    | LPAREN   expr RPAREN 
    ;



loop: WHILE   LPAREN {expressionStart();} expr {expressionEnd(LOOP_BLOCK_START);} RPAREN body {addLoopEndInstruction();}

cond: IF  LPAREN {expressionStart();} expr {expressionEnd(CONDITION_BLOCK_START);}  RPAREN body {addConditionEndInstruction();}

type: INT | FLOAT | BOOL;

body: {bodyStart();} LCURL stmts RCURL {bodyEnd();} ;

print: PRINT LPAREN pcont RPAREN TERMINATOR 
        
pcont : LABEL                                    {addPrintInstruction($1);}
        | STRING                                    {addPrintSInstruction($1);}
        ;

// printContent: STRING                    {addPrintInstruction($1);}
//     | STRING variadicPrint              {addPrintInstruction($1);}           
//     ;

// variadicPrint:COMMA LABEL
//     | COMMA LABEL variadicPrint

cmp: LT|MT|LE|ME|EQ|NE;

logicB: AND | OR;

%%
void yyerror(char * e){
    fprintf(stderr,"Error : %s\n",e);
}

void showUsage(char* progName){

    fprintf(stderr,"Usage: %s -i <input_file> -o <output_file>\n",progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
    int opt;
    char * inputFileName = NULL;


    while ((opt = getopt(argc, argv, "i:o:h")) != -1){

        switch(opt){

            case 'i':
               inputFileName = strdup(optarg);
                break;
            case 'o':
                 outputFileName = strdup(optarg);
                 break;
            case 'h':
                 showUsage(argv[0]);
                 break;
            default:
                showUsage(argv[0]);
        }
    }

    if (!inputFileName || !outputFileName)
    {
        showUsage(argv[0]);
    }


    yyin = fopen(inputFileName, "r");
    if (!yyin)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    programStart();
    yyparse();
    programEnd();

    if(yyin != stdin){
        fclose(yyin);
    }


    return 0;
}