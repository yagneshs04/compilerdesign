%%
[0-9]+   printf("Unsigned number: %s\n", yytext);
.        printf("Not an unsigned number\n");
%%
int main() {
    yylex();
    return 0;
}
