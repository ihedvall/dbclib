%top {
    #include <cstdint>
}
%{
    #include "dbcscanner.h"
    #undef  YY_DECL
    #define YY_DECL int dbc::DbcScanner::ddlex(dbc::DbcParser::value_type* yy_value)
    using token = dbc::DbcParser::token;
%}

%option prefix="dd"
%option 8bit
%option nounistd
%option noyywrap
%option debug
%option never-interactive
%option c++
%option yyclass="dbc:DbcScanner"
%option noinput
%option yylineno


ws              [ \t]+
signed_number   [-+]?[0-9]+
unsigned_number [0-9]+
hexnumber       0x[0-9a-fA-F]+
double_val      [-+]?[0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?
id              [a-zA-Z_]([_a-zA-Z0-9.]*)?
string          \"([^"\\]|(\\.))*\"
nl              [\n\r]


%s PRI VERSION TIMESTAMP HOSTNAME APPNAME PROCID MSGID SD SDELEMENT SDPAR SDVALUE MSG
%%
%{
            yylval = yy_value;
%}
[/]+.*         { } /* Remove comments */
"VERSION"              { return token::TAG_VERSION; }
"BO_"                  { return token::TAG_BO; }
"BS_"                  { return token::TAG_BS; }
"BU_"                  { return token::TAG_BU; }
"SG_"                  { return token::TAG_SG; }
"EV_"                  { return token::TAG_EV; }
"SIG_VALTYPE_"         { return token::TAG_SIG_VALTYPE; }
"NS_"                  { return token::TAG_NS;}
"INT"                  { return token::TAG_INT; }
"FLOAT"                { return token::TAG_FLOAT; }
"NAN"                  { return token::TAG_NAN; }
"STRING"               { return token::TAG_STRING; }
"ENUM"                 { return token::TAG_ENUM; }
"HEX"                  { return token::TAG_HEX; }

"NS_DESC_"             { return token::TAG_NS_DESC; }
"CM_"                  { return token::TAG_CM; }
"BA_DEF_"              { return token::TAG_BA_DEF; }
"BA_"                  { return token::TAG_BA; }
"VAL_"                 { return token::TAG_VAL; }
"CAT_DEF_"             { return token::TAG_CAT_DEF; }
"CAT_"                 { return token::TAG_CAT;  }

[fF][iI][lL][tT][eE][rR]      { return token::TAG_FILTER; }

"BA_DEF_DEF_"          { return token::TAG_BA_DEF_DEF;      }
"EV_DATA_"             { return token::TAG_EV_DATA;         }
"ENVVAR_DATA_"         { return token::TAG_ENVVAR_DATA;     }
"SGTYPE_"              { return token::TAG_SGTYPE;          }
"SGTYPE_VAL_"          { return token::TAG_SGTYPE_VAL;      }
"BA_DEF_SGTYPE_"       { return token::TAG_BA_DEF_SGTYPE;   }
"BA_SGTYPE_"           { return token::TAG_BA_SGTYPE;       }
"SIG_TYPE_REF_"        { return token::TAG_SIG_TYPE_REF;    }
"VAL_TABLE_"           { return token::TAG_VAL_TABLE;       }
"SIG_GROUP_"           { return token::TAG_SIG_GROUP;       }
"SIGTYPE_VALTYPE_"     { return token::TAG_SIGTYPE_VALTYPE; }
"BO_TX_BU_"            { return token::TAG_BO_TX_BU;        }
"BA_DEF_REL_"          { return token::TAG_BA_DEF_REL;      }
"BA_REL_"              { return token::TAG_BA_REL;          }
"BA_DEF_DEF_REL_"      { return token::TAG_BA_DEF_DEF_REL;  }
"BU_SG_REL_"           { return token::TAG_BU_SG_REL;       }
"BU_EV_REL_"           { return token::TAG_BU_EV_REL;       }
"BU_BO_REL_"           { return token::TAG_BU_BO_REL;       }
"SG_MUL_VAL_"          { return token::TAG_SG_MUL_VAL;      }

"DUMMY_NODE_VECTOR"[0-9]+ {
   try {
      const auto index = std::stoi(yytext + 17);
      yylval->build(index);
   } catch (const std::exception& ) {
      yylval->build<int>(0);
   }
   return token::TAG_DUMMY_NODE_VECTOR;
}

{nl}             {}
{ws}             {}
{id}             {
                   const std::string temp(yytext);
                   yylval->build(temp);
                   return token::ID_VAL;
                 }
"+"              { return token::TAG_PLUS; }
"-"              { return token::TAG_MINUS; }
{string}         {
                   const size_t len = strlen(yytext);
                   std::string temp;
                   if (len > 2) {
                     temp = yytext + 1;
                     temp.pop_back();
                   }
                   yylval->build(temp);
                   return token::STRING_VAL;
                 }

{signed_number}  {
                   int64_t temp = 0;
                   try {
                     temp = std::stoll(yytext);
                   } catch (const std::exception& ) {

                   }
                   yylval->build(temp);
                   return token::INT_VAL;
                 }



{hexnumber}      {
		uint64_t address = 0;
		for ( size_t index = 0; yytext[ index ] != '\0'; ++index ) {
			if ( index < 2 ) continue;
			const char token = yytext[index];
			switch ( token ) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				address *= 16;
				address += token - '0';
				break;

			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				address *= 16;
				address += token - 'A' + 10;
				break;

			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				address *= 16;
				address += token - 'a' + 10;
				break;

			default:
				break;
			}
		}

		yylval->build(address);
	    return token::HEX_VAL;
    }
{double_val}     {
                   double temp = 0.0;
                   try {
                     temp = std::stod(yytext);
                   } catch (const std::exception&) {

                   }
                   yylval->build<double>(temp);
                   return token::DOUBLE_VAL;
                 }

":"              { return token::TAG_COLON; }
";"              { return token::TAG_SEMICOLON; }
"|"              { return token::TAG_SEP; }
","              { return token::TAG_COMMA; }
"@"              { return token::TAG_AT; }

"["              { return token::TAG_BOX_OPEN; }
"]"              { return token::TAG_BOX_CLOSE; }
"("              { return token::TAG_PAR_OPEN; }
")"              { return token::TAG_PAR_CLOSE; }


.                {}
%%

