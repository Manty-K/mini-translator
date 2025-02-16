%{
    #include "y.tab.h"   
%}


%%

\"([^\"]*)\"			{ yylval.s = strndup(yytext+1,yyleng-2);return STRING; }

"int"                   {yylval.s = strdup(yytext); return INT;}

"float"                   {yylval.s = strdup(yytext); return FLOAT;}

"bool"                   {yylval.s = strdup(yytext); return BOOL;}

"print"                     {yylval.s = strdup(yytext); return PRINT;}


"if"                    {yylval.s = strdup(yytext); return IF;}

"while"                    {yylval.s = strdup(yytext); return WHILE;}

"{"                        {yylval.s = strdup(yytext); return LCURL;}
"}"                        {yylval.s = strdup(yytext); return RCURL;}

";"                         {yylval.s = strdup(yytext); return TERMINATOR;}

"("                        {yylval.s = strdup(yytext); return LPAREN;}
")"                        {yylval.s = strdup(yytext); return RPAREN;}


"<="    { yylval.s = strdup(yytext); return LE;}
">="    {yylval.s = strdup(yytext);  return ME;}

"<"         { yylval.s = strdup(yytext); return LT;}
">"         {yylval.s = strdup(yytext);  return MT;}

"!="     {yylval.s = strdup(yytext);  return NE;}
"=="    { yylval.s = strdup(yytext); return EQ;}


"="     { yylval.s = strdup(yytext); yylval.s = strdup(yytext);  return ASG;}

"+"     { yylval.s = strdup(yytext);  return PLUS;}
"-"     { yylval.s = strdup(yytext);  return MINUS;}
"*"     { yylval.s = strdup(yytext);  return MUL;}
"/"     { yylval.s = strdup(yytext);  return DIV;}

"&&"    { yylval.s = strdup(yytext); return AND;}
"||"    { yylval.s = strdup(yytext);  return OR;}
"!"     { yylval.s = strdup(yytext);  return NOT;}

","     { yylval.s = strdup(yytext);  return COMMA;}



[0-9]+(\.[0-9]+)?      { yylval.s = strdup(yytext);  return NUMBER;}
[a-zA-Z_]+[a-zA-Z0-9_]*      { yylval.s = strdup(yytext);  return LABEL;}


\n       ;

[\t ]   ;

.       ;

%%





