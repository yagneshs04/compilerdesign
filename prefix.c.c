%%
[-+]?[0-9]+   printf("Valid number: %s\n", yytext);
.             printf("Invalid input\n");
%%
int main() {
    yylex();
    return 0;
}
