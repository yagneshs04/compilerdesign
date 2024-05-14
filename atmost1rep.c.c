digit [0-9]
%%
{digit}({digit}|{digit}*{digit})?   printf("Matched: %s\n", yytext);
.                                   printf("No match\n");
%%
int main() {
    yylex();
    return 0;
}
