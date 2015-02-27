%{

#include "parser.tab.h"

extern unsigned int line;

%}

%%

"v"       { return VERT; }
"vn"      { return NORMAL; }
"vt"      { return TEXTURE; }
"o"       { return OBJECT; }
"s"       { return SETTING; }
"f"       { return FACE; }
"l"       { return ELL; }
"mtllib"  { return MTLLIB; }
"usemtl"  { return USEMTL; }
"/"       { return SLASH; }

[-]{0,1}[0-9.]+     { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z0-9._]+      { yylval.string = yytext; return STRING; }
#+.*\n              { line++; /*Comment*/ }
\n                  { line++; return EOL; }
[ \t\r\f\v]         { }
.                   { printf("Unknown: %s\n",yytext); }

%%
