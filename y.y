%{
    #include<stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "flatner/flatner.h"

    extern FILE * yyin;
    int yylex();
    void yyerror(char*);
%}


%token <s> INT FLOAT BOOL NUMBER LABEL ASG TERMINATOR  IF WHILE LCURL RCURL  LPAREN RPAREN LE ME LT MT EQ NE PLUS MINUS MUL DIV AND OR NOT PRINT

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

decl: type  LABEL TERMINATOR ;

assign:  LABEL ASG expr TERMINATOR ;

loop: WHILE expbody 

cond: IF expbody 

type: INT | FLOAT | BOOL;

expbody: LPAREN expr  RPAREN body 

body: {bodyStart();} LCURL stmts RCURL {bodyEnd();} ;

print: PRINT LABEL TERMINATOR ;



aexpr: term
    | term PLUS aexpr
    |  term MINUS  aexpr;

term: factor
    |  factor MUL term
    | factor DIV term
    ;

factor: NUMBER  
    | LABEL  
    | LPAREN   expr RPAREN 
    ;


c: aexpr
    |  aexpr cmp  c
    ;


expr : d
    | expr logicB  d
    ;

d : c
    | NOT  d
    ;

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
    char * outputFileName = NULL;


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


    openOutfile(outputFileName);
    programStart();
    yyparse();
    programEnd();

    closeOutfile();


    if(yyin != stdin){
        fclose(yyin);
    }
    free(outputFileName);


    return 0;
}