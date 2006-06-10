/* Started with net.y rules, removed left recursion and performed left factoring
   This was done so grammar will work with LL(k) parser 
   complex had to be taken out of scaler due to ambiguity with T_LPAR */

header{
#include <iostream>
#include "Parse.h"
}

options {
        language="Cpp";
}

class NetParser extends Parser;
options {
	k = 3;
	exportVocab=DXNet;
}


start:	(top)* c_0 ;

c_0:	{ };

top	options {defaultErrorHandler = true;}
	: ( statement 
	|   macro) 
	;

macro	:	K_MACRO T_ID T_LPAR formal_s0 T_RPAR 
		(T_RA T_LPAR formal_s0 T_RPAR)? 
		attributes
         	block { ParseEndOfMacroDefinition();}
	;

formal_s0       : (formal attributes (formal_s)*)?
		;

formal_s       : T_COMMA formal attributes 
		;

formal          : T_ID
                | T_ID T_ASSIGN T_ID (formal_0)? 
                | T_ID T_ASSIGN constant 	//complex causes amiguity
                | T_ID T_ASSIGN T_LPAR complex T_RPAR
                ;

formal_0        : T_ASSIGN constant
                | T_ASSIGN T_LPAR complex T_RPAR
                ;

/*
 * Block:
 */

block           : T_LBRA statement_s T_RBRA
                ;

/*
 * Statements:
 */

statement_s     : (statement)+
                ;

/*
 * Put the LIST_CREATE here for the top level (for adding loop increments).
 */

statement       : block
                | assignment    attributes T_SEMI
                | function_call attributes T_SEMI
                | include
                | comment
                ;

/*
 * include
 */
include         : K_INCLUDE string
                ;

/*
 * Assignments with left factoring
 */

assignment      : l_value_s T_ASSIGN t_assignment
                | T_ID T_PP
                | T_ID T_MM
                ;

t_assignment    : function_call
		| expression_s
		| r_value
                ;

/*
 * Attribute Structure:
 */

attributes      : (T_LSQB (attribute (attribute_s)*)? T_RSQB)?
                ;

attribute_s     : T_COMMA attribute 
                ;

/*
 * ddz
 */
attribute       : id:T_ID T_COLON 
		(str:T_STRING
                {
		  std::string n_str;
                  n_str.assign(str->getText(),1,str->getText().size()-2);
                  ParseStringAttribute(id->getText().c_str(), n_str.c_str());
                }
		| i_value:T_INT 
		 { 
		  ParseIntAttribute(id->getText().c_str(), atoi(i_value->getText().c_str()));
		 } 
		)
                ;

/*
 * Function Call:
 */

function_call   : fid:T_ID  
                {
                    ParseFunctionID(fid->getText().c_str());
                }
                T_LPAR argument_s T_RPAR
                ;

/*
 * Argument Structure:
 */

argument_s      : (argument (T_COMMA argument)* )?
                ;

argument        : value
                | T_ID T_ASSIGN value
                ;

value           {std::string c_value;}
                : c_value=constant
                {
                    ParseArgument(c_value.c_str(),0);
                }
                | id:T_ID
                {
                    yylineno = id->getLine();
                    ParseArgument(id->getText().c_str(),1);
                }
                | T_LPAR complex T_RPAR
                ;

/*
 * Comment:
 */

comment         : (D_COMMENT 
		| T_COMMENT
		| s_com:S_COMMENT 
		{ std::string ns_com;
		  ns_com.assign(s_com->getText(),2,s_com->getText().size()-2);
		  s_com->setText(ns_com);
		  yylineno = s_com->getLine();
                  ParseComment(s_com->getText().c_str());
                }) 
		;

/*
 * Arithmetic Expressions:
 */

expression_s    : expression (expression_s0)*
                ;

expression_s0   : T_COMMA expression 
                | T_COMMA r_value 
                ;
expression      : constant		// complex not included
                | T_LPAR expression_c T_RPAR
                ;

expression_c    : expression 
		| r_value 
		| complex 		//complex constants
		;

/*
 * Definitions for constant data types:
 */

constant returns [std::string c_str] {c_str="";}
                : c_str = real
                | c_str = tensor
                | c_str = list
                | c_str = string
                | K_NULL {c_str="NULL";}
                ;
                                                                                
list returns [std::string l_val] {std::string r_val, s_val; l_val="{";}
                : T_LBRA s_val = scalar_s T_RBRA {l_val+=s_val + "}";}
                | T_LBRA s_val = tensor_s T_RBRA {l_val+=s_val + "}";}
                | T_LBRA s_val = string_s T_RBRA {l_val+=s_val + "}";}
                | T_LBRA r_val = real T_DOTDOT s_val = real
                  {l_val += r_val + ".." + s_val;}
                  r_val = list_r {l_val += r_val;}
                ;
                                                                                
list_r returns [std::string l_val] {std::string r_val;}
                : T_RBRA {l_val="}";}
                | T_COLON r_val=real T_RBRA {l_val=":"+r_val+"}";}
                ;
                                                                                
tensor_s returns [std::string ts_val] {std::string s_val="";}
                : ts_val = tensor
                  (s_val=tensor {ts_val+=" " + s_val;}
                  | T_COMMA s_val=tensor { ts_val += "," + s_val;})*
                ;
                                                                                
tensor returns [std::string t_val] {std::string s_val; t_val="[";}
                : T_LSQB s_val = scalar_s T_RSQB {t_val+=s_val + "]";}
                | T_LSQB s_val = tensor_s T_RSQB {t_val+=s_val + "]";}
                ;
                                                                                
scalar_s returns [std::string ss_val] {std::string s_val;}
                : ss_val = scalar
                  (s_val = scalar {ss_val += " " + s_val;}
                  | T_COMMA s_val = scalar {ss_val += "," + s_val;})*
                ;
                                                                                
scalar  returns [std::string s_val] {std::string c_val="";}
                : s_val = real
                | T_LPAR c_val = complex T_RPAR {s_val="("+c_val+")";}
                ;
                                                                                
real returns [std::string r_val] {r_val="";}
                : r_val = int_type
                | r_val = float_type
                ;
                                                                                
complex returns [std::string c_val] {std::string r_val, q_val="";}
                : c_val = int_type  T_COMMA r_val = int_type
                  (q_val = quaternion_i)? {c_val+=","+r_val + q_val;}
                | c_val = float_type T_COMMA r_val = float_type
                  (q_val = quaternion_f)? {c_val+=","+r_val + q_val;}
                ;
                                                                                
quaternion_i returns [std::string q_val=","] {std::string val1, val2;}
                : T_COMMA val1 = int_type   T_COMMA  val2 = int_type
                  { q_val += val1 + "," + val2;}
                ;
                                                                                
quaternion_f returns [std::string q_val=","] {std::string val1, val2;}
                : T_COMMA val1=float_type T_COMMA val2=float_type
                  { q_val += val1 + "," + val2;}
                ;
                                                                                
                                                                             
int_type returns [std::string r_val]
                : i_val:T_INT {r_val=i_val->getText();}
                ;
                                                                                
float_type returns [std::string r_val]
                : f_val:T_FLOAT {r_val=f_val->getText();}
                ;
                                                                                
string_s returns [std::string ss_val] {std::string s_val;}
                : ss_val = string
                  (s_val = string {ss_val+=" "+s_val;}
                  | T_COMMA s_val = string {ss_val+=","+s_val;} )*
                ;
                                                                                
string returns [std::string n_str]
                : str:T_STRING
                { 
                  n_str.assign(str->getText(),1,str->getText().size()-2);
                  //n_str[str->getText().size()-2]='\000';
                  //str->setText(n_str);
                }
                ;

l_value_s       : l_value attributes (T_COMMA l_value attributes)*
		;

l_value         : id:T_ID
                {
                    ParseLValue(id->getText().c_str());
                }
                ;

r_value         : id:T_ID
                {
                    yylineno = id->getLine();
                    ParseRValue(id->getText().c_str());
                }
                ;

empty           :
                {
                }
                ;

v_TRUE: (K_TRUE|K_ON) ;
v_FALSE:(K_FALSE|K_OFF);


class NetLexer extends Lexer;
options {
        k=3;
	testLiterals = true;
	caseSensitiveLiterals = true;
}

tokens {
	K_TRUE = "true";
	K_FALSE = "false";
	K_CANCEL = "cancel";
	K_BACKWARD = "backward";
	K_FORWARD = "forward";
	K_INCLUDE = "include";
	K_LOOP = "loop";
	K_MACRO = "macro";
	K_MODULE = "module";
	K_NULL = "NULL";
	K_OFF = "off";
	K_ON = "on";
	K_PAUSE = "pause";
	K_PALINDROME = "palindrome";
	K_PLAY = "play";
	K_QUIT = "quit";
	K_STEP = "step";
	K_STOP = "stop";
	K_VCR = "sequence";		//note this is K_SEQUENCE in uipp .lex
	P_ACK =	"$ack";
	P_BACKGROUND = "$bac";
	P_DATA = "$dat";
	P_FORGROUND = "$for";
	P_ERROR = "$err";
	P_IMPORT = "$imp";
	P_INFO = "$inf";
	P_INTERRUPT = "$int";
	P_LINQ = "$lin";
	P_LRESP = "$lre";
	P_MACRO = "$mac";
	P_MESSAGE = "$mes";
	P_SINQ = "$sin";
	P_SRESP = "$sre";
	P_SYSTEM = "$sys";
	P_VINQ = "$vin";
	P_VRESP = "$vre";
}

//Logic Operators
L_AND:  "&&";	//(".AND."|"&&"|"AND");
L_OR:	"||";	//(".OR."|"||"|"OR");
L_NOT:	"!";	//(".NOT."|"!"|"NOT");
L_EQ:	"==";	//(".EQ."|"==");
L_NEQ:	"!=";	//(".NE."|"!="|"<>");
L_LEQ:	"<=";	//(".LE."|"<=");
L_GEQ:  ">=";	//(".GE."|">=");
L_LT:	"<";	//(".LT."|"<");
L_GT:	">";	//(".GT."|">");

/*
A_PLUS: "+";	//I don't see where these arithmetic operators are used 
A_MINUS:"-"; 	//Commented out so T_INT and T_FLOAT recognized
A_TIMES:"*";
A_DIV:	"/";	//("/"|"div"|"DIV");
A_MOD:	"%";	//("%"|"mod"|"MOD");
A_EXP:	("^");	//("^"|"**");
*/

T_BAR:	"|";
T_LPAR:	"(";
T_RPAR: ")";
T_LBRA: "{";
T_RBRA: "}";
T_LSQB: "[";
T_RSQB: "]";
T_ASSIGN: "=";
T_COMMA:",";
T_COLON:":";
T_SEMI: ";";
T_PP:	"++";
T_MM:	"--";
T_RA:	"->";
//T_DOTDOT:"..";  set in T_INT

WS 	:       (' '
        |       '\t'
        |       '\n'  { newline(); }
        |       '\r')
                { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
        ;

protected	//protected - can only be called by a Lexer Rule
AL  :   ( 'a'..'z'|'A'..'Z'|'_'|'@' ) ;
protected
ALN :   ( 'a'..'z'|'A'..'Z'|'_'|'@'|'0'..'9' ) ;
protected
O   :	'0'..'7' ;
protected
D   :   '0'..'9' ;
protected
X   :	('0'..'9'|'a'..'f'|'A'..'F') ;
protected
US  :	('-'|'+')?  ;
protected
E   :	('e'|'E')(US)(D)+ ;

T_ID	options {testLiterals=true;} :
	(AL)(ALN)*;

T_EXID  options {testLiterals=true;} :
	( "?" | "?" (ALN | "?")+ ) ;

// a numeric literal - adapted from cpp/java example
T_INT
        {bool isDecimal=false; }
    :   '.' //{$setType(T_DOT);}    T_DOT undefined in Lexer compile. Need to use in Parser  
            ( '.' {_ttype = T_DOTDOT;}
              | (D)+ (E)?  { _ttype = T_FLOAT; }
            )?
    |   US
        ( '0' {isDecimal = true;} // special case for just '0'
                (  ('x'|'X')          //hex
                     ( options { warnWhenFollowAmbig=false; }
                      : X)+
                                                                                
                |       //float or double with leading zero
                    ((D)+ ('.'|E)) => (D)+
                )?
        |  ('1'..'9') (D)*  {isDecimal=true;} // non-zero decimal
        )
        (
                // only check to see if it's a float if looks like decimal so far
                {isDecimal}?
            (   '.' (D)* (E)?
            |   E
            )
            { _ttype = T_FLOAT; }
        )?
        ;

// string literals - taken from antlr java example
// I added the '?' nd '%' since it crashed on Compute strings with each, though it now is 
// amibiguous. NetLexer.cpp does not have 0x3f and 0x25 otherwise. Antlr bug?
T_STRING
	:	'"' (ESC | '?' | '%' | ~('"'|'\\'|'\n'|'\r'))* '"'
	//:	'"' (ESC | ~('"'|'\\'|'\n'|'\r'))* '"'
        ;

// escape sequence -- note that this is protected; it can only be called
//   from another lexer rule -- it will not ever directly return a token to
//   the parser
// There are various ambiguities hushed in this rule.  The optional
// '0'...'9' digit matches should be matched here rather than letting
// them go back to STRING_LITERAL to be matched.  ANTLR does the
// right thing by matching immediately; hence, it's ok to shut off
// the FOLLOW ambig warnings.
protected
ESC
        :       '\\'
                (       'n'
                |       'r'
                |       't'
                |       'b'
                |       'f'
                |       '"'
                |       '\''
                |       '\\'
                |       ('u')+ X X X X
                |       '0'..'3'
                        (
                                options {
                                        warnWhenFollowAmbig = false;
                                }
                        :       '0'..'7'
                                (
                                        options {
                                                warnWhenFollowAmbig = false;
                                        }
                                :       '0'..'7'
                                )?
                        )?
                |       '4'..'7'
                        (
                                options {
                                        warnWhenFollowAmbig = false;
                                }
                        :       '0'..'7'
                        )?
                )
        ;

D_COMMENT:	"$" ( ~('\n'|'\r') )* 
		;
T_COMMENT:	"#" ( ~('\n'|'\r') )* 
		;
S_COMMENT:	"//" ( '*' | ~('\n'|'\r') )* 
		;
