%%
[a-z]*[aeiou][a-z]*[aeiou][a-z]*[aeiou][a-z]*[aeiou][a-z]*[aeiou][a-z]*   printf("Matched: %s\n", yytext);
.                                                                        printf("No match\n");
%%
int main() {
    yylex();
    return 0;
}
