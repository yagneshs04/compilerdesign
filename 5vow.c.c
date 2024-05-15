other   [bcdfghjklmnpqrstvwxyz]

%%
other* a (other|a)* e (other|e)* i (other|i)* o (other|o)* u (other|u)*   printf("Matched: %s\n", yytext);
.                                                                        printf("No match\n");


%%
int main() {
    yylex();
    return 0;
}
