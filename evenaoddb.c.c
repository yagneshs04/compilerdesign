%%
(a*ba*ba*)+   printf("Matched: %s\n", yytext);
.             printf("No match\n");
%%
int main() {
    yylex();
    return 0;
}
