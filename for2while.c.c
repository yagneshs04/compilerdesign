%{
#include <stdio.h>
#include <string.h>
%}

%%
"for"       { printf("while("); BEGIN FORLOOP; }
.           ;
<FORLOOP>{
    [^;]+;   printf("%s", yytext); yymore();
    ";"      { printf("; "); }
    [^;]+;   printf("%s", yytext); yymore();
    ";"      { printf("; "); }
    [^)]+    { printf("%s", yytext); yymore(); }
    \)       { printf(") {"); BEGIN NORMAL; }
}

<INITIAL>{
    \n        { printf("\n"); }
    [^\n]     { printf("%s", yytext); }
}

<NORMAL>{
    "{"       { printf(" {"); BEGIN INITIAL; }
    [^;]+;    { printf("%s", yytext); }
    ";"       { printf(";"); }
    [^;]+;    { printf("%s", yytext); }
    ";"       { printf(";"); }
    [^\n]+    { printf("%s", yytext); }
    \n        { printf("\n"); }
}
%%

int main() {
    yylex();
    return 0;
}
