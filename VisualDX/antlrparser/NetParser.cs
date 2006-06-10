// $ANTLR 2.7.6 (2005-12-22): "netcs.g" -> "NetParser.cs"$


namespace WinDX.UI
{
	// Generate the header common to all output files.
	using System;
	
	using TokenBuffer              = antlr.TokenBuffer;
	using TokenStreamException     = antlr.TokenStreamException;
	using TokenStreamIOException   = antlr.TokenStreamIOException;
	using ANTLRException           = antlr.ANTLRException;
	using LLkParser = antlr.LLkParser;
	using Token                    = antlr.Token;
	using IToken                   = antlr.IToken;
	using TokenStream              = antlr.TokenStream;
	using RecognitionException     = antlr.RecognitionException;
	using NoViableAltException     = antlr.NoViableAltException;
	using MismatchedTokenException = antlr.MismatchedTokenException;
	using SemanticException        = antlr.SemanticException;
	using ParserSharedInputState   = antlr.ParserSharedInputState;
	using BitSet                   = antlr.collections.impl.BitSet;
	
	public 	class NetParser : antlr.LLkParser
	{
		public const int EOF = 1;
		public const int NULL_TREE_LOOKAHEAD = 3;
		public const int K_MACRO = 4;
		public const int T_ID = 5;
		public const int T_LPAR = 6;
		public const int T_RPAR = 7;
		public const int T_RA = 8;
		public const int T_COMMA = 9;
		public const int T_ASSIGN = 10;
		public const int T_LBRA = 11;
		public const int T_RBRA = 12;
		public const int T_SEMI = 13;
		public const int K_INCLUDE = 14;
		public const int T_PP = 15;
		public const int T_MM = 16;
		public const int T_LSQB = 17;
		public const int T_RSQB = 18;
		public const int T_COLON = 19;
		public const int T_STRING = 20;
		public const int T_INT = 21;
		public const int D_COMMENT = 22;
		public const int T_COMMENT = 23;
		public const int S_COMMENT = 24;
		public const int K_NULL = 25;
		public const int T_DOTDOT = 26;
		public const int T_FLOAT = 27;
		public const int K_TRUE = 28;
		public const int K_ON = 29;
		public const int K_FALSE = 30;
		public const int K_OFF = 31;
		public const int K_CANCEL = 32;
		public const int K_BACKWARD = 33;
		public const int K_FORWARD = 34;
		public const int K_LOOP = 35;
		public const int K_MODULE = 36;
		public const int K_PAUSE = 37;
		public const int K_PALINDROME = 38;
		public const int K_PLAY = 39;
		public const int K_QUIT = 40;
		public const int K_STEP = 41;
		public const int K_STOP = 42;
		public const int K_VCR = 43;
		public const int P_ACK = 44;
		public const int P_BACKGROUND = 45;
		public const int P_DATA = 46;
		public const int P_FORGROUND = 47;
		public const int P_ERROR = 48;
		public const int P_IMPORT = 49;
		public const int P_INFO = 50;
		public const int P_INTERRUPT = 51;
		public const int P_LINQ = 52;
		public const int P_LRESP = 53;
		public const int P_MACRO = 54;
		public const int P_MESSAGE = 55;
		public const int P_SINQ = 56;
		public const int P_SRESP = 57;
		public const int P_SYSTEM = 58;
		public const int P_VINQ = 59;
		public const int P_VRESP = 60;
		public const int L_AND = 61;
		public const int L_OR = 62;
		public const int L_NOT = 63;
		public const int L_EQ = 64;
		public const int L_NEQ = 65;
		public const int L_LEQ = 66;
		public const int L_GEQ = 67;
		public const int L_LT = 68;
		public const int L_GT = 69;
		public const int T_BAR = 70;
		public const int WS = 71;
		public const int AL = 72;
		public const int ALN = 73;
		public const int O = 74;
		public const int D = 75;
		public const int X = 76;
		public const int US = 77;
		public const int E = 78;
		public const int T_EXID = 79;
		public const int ESC = 80;
		
		
		protected void initialize()
		{
			tokenNames = tokenNames_;
		}
		
		
		protected NetParser(TokenBuffer tokenBuf, int k) : base(tokenBuf, k)
		{
			initialize();
		}
		
		public NetParser(TokenBuffer tokenBuf) : this(tokenBuf,3)
		{
		}
		
		protected NetParser(TokenStream lexer, int k) : base(lexer,k)
		{
			initialize();
		}
		
		public NetParser(TokenStream lexer) : this(lexer,3)
		{
		}
		
		public NetParser(ParserSharedInputState state) : base(state,3)
		{
			initialize();
		}
		
	public void start() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{    // ( ... )*
				for (;;)
				{
					if ((tokenSet_0_.member(LA(1))))
					{
						top();
					}
					else
					{
						goto _loop3_breakloop;
					}
					
				}
_loop3_breakloop:				;
			}    // ( ... )*
			c_0();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_1_);
		}
	}
	
	public void top() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case T_ID:
				case T_LBRA:
				case K_INCLUDE:
				case D_COMMENT:
				case T_COMMENT:
				case S_COMMENT:
				{
					statement();
					break;
				}
				case K_MACRO:
				{
					macro();
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_2_);
		}
	}
	
	public void c_0() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_1_);
		}
	}
	
	public void statement() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_LBRA:
			{
				block();
				break;
			}
			case K_INCLUDE:
			{
				include();
				break;
			}
			case D_COMMENT:
			case T_COMMENT:
			case S_COMMENT:
			{
				comment();
				break;
			}
			default:
				if ((LA(1)==T_ID) && (tokenSet_3_.member(LA(2))))
				{
					assignment();
					attributes();
					match(T_SEMI);
				}
				else if ((LA(1)==T_ID) && (LA(2)==T_LPAR)) {
					function_call();
					attributes();
					match(T_SEMI);
				}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			break; }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_4_);
		}
	}
	
	public void macro() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			match(K_MACRO);
			match(T_ID);
			match(T_LPAR);
			formal_s0();
			match(T_RPAR);
			{
				switch ( LA(1) )
				{
				case T_RA:
				{
					match(T_RA);
					match(T_LPAR);
					formal_s0();
					match(T_RPAR);
					break;
				}
				case T_LBRA:
				case T_LSQB:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
			attributes();
			block();
			Network.ParseState.network.ParseEndOfMacroDefinition();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_2_);
		}
	}
	
	public void formal_s0() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case T_ID:
				{
					formal();
					attributes();
					{    // ( ... )*
						for (;;)
						{
							if ((LA(1)==T_COMMA))
							{
								formal_s();
							}
							else
							{
								goto _loop12_breakloop;
							}
							
						}
_loop12_breakloop:						;
					}    // ( ... )*
					break;
				}
				case T_RPAR:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_5_);
		}
	}
	
	public void attributes() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case T_LSQB:
				{
					match(T_LSQB);
					{
						switch ( LA(1) )
						{
						case T_ID:
						{
							attribute();
							{    // ( ... )*
								for (;;)
								{
									if ((LA(1)==T_COMMA))
									{
										attribute_s();
									}
									else
									{
										goto _loop29_breakloop;
									}
									
								}
_loop29_breakloop:								;
							}    // ( ... )*
							break;
						}
						case T_RSQB:
						{
							break;
						}
						default:
						{
							throw new NoViableAltException(LT(1), getFilename());
						}
						 }
					}
					match(T_RSQB);
					break;
				}
				case T_RPAR:
				case T_COMMA:
				case T_ASSIGN:
				case T_LBRA:
				case T_SEMI:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_6_);
		}
	}
	
	public void block() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			match(T_LBRA);
			statement_s();
			match(T_RBRA);
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_4_);
		}
	}
	
	public void formal() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((LA(1)==T_ID) && (LA(2)==T_RPAR||LA(2)==T_COMMA||LA(2)==T_LSQB))
			{
				match(T_ID);
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_ASSIGN) && (LA(3)==T_ID)) {
				match(T_ID);
				match(T_ASSIGN);
				match(T_ID);
				{
					switch ( LA(1) )
					{
					case T_ASSIGN:
					{
						formal_0();
						break;
					}
					case T_RPAR:
					case T_COMMA:
					case T_LSQB:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					 }
				}
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_ASSIGN) && (tokenSet_7_.member(LA(3)))) {
				match(T_ID);
				match(T_ASSIGN);
				constant();
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_ASSIGN) && (LA(3)==T_LPAR)) {
				match(T_ID);
				match(T_ASSIGN);
				match(T_LPAR);
				complex();
				match(T_RPAR);
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_8_);
		}
	}
	
	public void formal_s() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			match(T_COMMA);
			formal();
			attributes();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_9_);
		}
	}
	
	public void formal_0() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((LA(1)==T_ASSIGN) && (tokenSet_7_.member(LA(2))))
			{
				match(T_ASSIGN);
				constant();
			}
			else if ((LA(1)==T_ASSIGN) && (LA(2)==T_LPAR)) {
				match(T_ASSIGN);
				match(T_LPAR);
				complex();
				match(T_RPAR);
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_8_);
		}
	}
	
	public string  constant() //throws RecognitionException, TokenStreamException
{
		string c_str="";
		
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_INT:
			case T_FLOAT:
			{
				c_str=real();
				break;
			}
			case T_LSQB:
			{
				c_str=tensor();
				break;
			}
			case T_LBRA:
			{
				c_str=list();
				break;
			}
			case T_STRING:
			{
				c_str=stringv();
				break;
			}
			case K_NULL:
			{
				match(K_NULL);
				c_str="NULL";
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_10_);
		}
		return c_str;
	}
	
	public string  complex() //throws RecognitionException, TokenStreamException
{
		string c_val="";
		
		string r_val, q_val="";
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_INT:
			{
				c_val=int_type();
				match(T_COMMA);
				r_val=int_type();
				{
					switch ( LA(1) )
					{
					case T_COMMA:
					{
						q_val=quaternion_i();
						break;
					}
					case T_RPAR:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					 }
				}
				c_val+=","+r_val + q_val;
				break;
			}
			case T_FLOAT:
			{
				c_val=float_type();
				match(T_COMMA);
				r_val=float_type();
				{
					switch ( LA(1) )
					{
					case T_COMMA:
					{
						q_val=quaternion_f();
						break;
					}
					case T_RPAR:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					 }
				}
				c_val+=","+r_val + q_val;
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_5_);
		}
		return c_val;
	}
	
	public void statement_s() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{ // ( ... )+
				int _cnt20=0;
				for (;;)
				{
					if ((tokenSet_11_.member(LA(1))))
					{
						statement();
					}
					else
					{
						if (_cnt20 >= 1) { goto _loop20_breakloop; } else { throw new NoViableAltException(LT(1), getFilename());; }
					}
					
					_cnt20++;
				}
_loop20_breakloop:				;
			}    // ( ... )+
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_12_);
		}
	}
	
	public void assignment() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((LA(1)==T_ID) && (LA(2)==T_COMMA||LA(2)==T_ASSIGN||LA(2)==T_LSQB))
			{
				l_value_s();
				match(T_ASSIGN);
				t_assignment();
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_PP)) {
				match(T_ID);
				match(T_PP);
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_MM)) {
				match(T_ID);
				match(T_MM);
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_13_);
		}
	}
	
	public void function_call() //throws RecognitionException, TokenStreamException
{
		
		IToken  fid = null;
		
		try {      // for error handling
			fid = LT(1);
			match(T_ID);
			
			Network.ParseState.network.ParseFunctionID(fid.getText());
			
			match(T_LPAR);
			argument_s();
			match(T_RPAR);
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_13_);
		}
	}
	
	public void include() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			match(K_INCLUDE);
			stringv();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_4_);
		}
	}
	
	public void comment() //throws RecognitionException, TokenStreamException
{
		
		IToken  s_com = null;
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case D_COMMENT:
				{
					match(D_COMMENT);
					break;
				}
				case T_COMMENT:
				{
					match(T_COMMENT);
					break;
				}
				case S_COMMENT:
				{
					s_com = LT(1);
					match(S_COMMENT);
					string ns_com;
							  ns_com = s_com.getText().Substring(2);
							  s_com.setText(ns_com);
							  Network.ParseState.lineno = s_com.getLine();
					Network.ParseState.network.ParseComment(s_com.getText());
					
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_4_);
		}
	}
	
	public string  stringv() //throws RecognitionException, TokenStreamException
{
		string n_str="";
		
		IToken  str = null;
		
		try {      // for error handling
			str = LT(1);
			match(T_STRING);
			
			n_str=str.getText().Substring(1,str.getText().Length-2);
			//n_str[str->getText().size()-2]='\000';
			//str->setText(n_str);
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_14_);
		}
		return n_str;
	}
	
	public void l_value_s() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			l_value();
			attributes();
			{    // ( ... )*
				for (;;)
				{
					if ((LA(1)==T_COMMA))
					{
						match(T_COMMA);
						l_value();
						attributes();
					}
					else
					{
						goto _loop73_breakloop;
					}
					
				}
_loop73_breakloop:				;
			}    // ( ... )*
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_15_);
		}
	}
	
	public void t_assignment() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((LA(1)==T_ID) && (LA(2)==T_LPAR))
			{
				function_call();
			}
			else if ((tokenSet_16_.member(LA(1)))) {
				expression_s();
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_SEMI||LA(2)==T_LSQB)) {
				r_value();
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_13_);
		}
	}
	
	public void expression_s() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			expression();
			{    // ( ... )*
				for (;;)
				{
					if ((LA(1)==T_COMMA))
					{
						expression_s0();
					}
					else
					{
						goto _loop44_breakloop;
					}
					
				}
_loop44_breakloop:				;
			}    // ( ... )*
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_13_);
		}
	}
	
	public void r_value() //throws RecognitionException, TokenStreamException
{
		
		IToken  id = null;
		
		try {      // for error handling
			id = LT(1);
			match(T_ID);
			
			Network.ParseState.lineno = id.getLine();
			Network.ParseState.network.ParseRValue(id.getText());
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_10_);
		}
	}
	
	public void attribute() //throws RecognitionException, TokenStreamException
{
		
		IToken  id = null;
		IToken  str = null;
		IToken  i_value = null;
		
		try {      // for error handling
			id = LT(1);
			match(T_ID);
			match(T_COLON);
			{
				switch ( LA(1) )
				{
				case T_STRING:
				{
					str = LT(1);
					match(T_STRING);
					
							  String n_str;
					n_str=str.getText().Substring(1,str.getText().Length-2);
					Network.ParseState.network.ParseStringAttribute(id.getText(), n_str);
					
					break;
				}
				case T_INT:
				{
					i_value = LT(1);
					match(T_INT);
					
							  Network.ParseState.network.ParseIntAttribute(id.getText(), Int32.Parse(i_value.getText()));
							
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_17_);
		}
	}
	
	public void attribute_s() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			match(T_COMMA);
			attribute();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_17_);
		}
	}
	
	public void argument_s() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case T_ID:
				case T_LPAR:
				case T_LBRA:
				case T_LSQB:
				case T_STRING:
				case T_INT:
				case K_NULL:
				case T_FLOAT:
				{
					argument();
					{    // ( ... )*
						for (;;)
						{
							if ((LA(1)==T_COMMA))
							{
								match(T_COMMA);
								argument();
							}
							else
							{
								goto _loop37_breakloop;
							}
							
						}
_loop37_breakloop:						;
					}    // ( ... )*
					break;
				}
				case T_RPAR:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_5_);
		}
	}
	
	public void argument() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((tokenSet_18_.member(LA(1))) && (tokenSet_19_.member(LA(2))))
			{
				value();
			}
			else if ((LA(1)==T_ID) && (LA(2)==T_ASSIGN)) {
				match(T_ID);
				match(T_ASSIGN);
				value();
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_9_);
		}
	}
	
	public void value() //throws RecognitionException, TokenStreamException
{
		
		IToken  id = null;
		string c_value;
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_LBRA:
			case T_LSQB:
			case T_STRING:
			case T_INT:
			case K_NULL:
			case T_FLOAT:
			{
				c_value=constant();
				
				Network.ParseState.network.ParseArgument(c_value,false);
				
				break;
			}
			case T_ID:
			{
				id = LT(1);
				match(T_ID);
				
				Network.ParseState.lineno = id.getLine();
				Network.ParseState.network.ParseArgument(id.getText(),true);
				
				break;
			}
			case T_LPAR:
			{
				match(T_LPAR);
				complex();
				match(T_RPAR);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_9_);
		}
	}
	
	public void expression() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_LBRA:
			case T_LSQB:
			case T_STRING:
			case T_INT:
			case K_NULL:
			case T_FLOAT:
			{
				constant();
				break;
			}
			case T_LPAR:
			{
				match(T_LPAR);
				expression_c();
				match(T_RPAR);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_10_);
		}
	}
	
	public void expression_s0() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((LA(1)==T_COMMA) && (tokenSet_16_.member(LA(2))))
			{
				match(T_COMMA);
				expression();
			}
			else if ((LA(1)==T_COMMA) && (LA(2)==T_ID)) {
				match(T_COMMA);
				r_value();
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_20_);
		}
	}
	
	public void expression_c() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			if ((tokenSet_16_.member(LA(1))) && (tokenSet_21_.member(LA(2))))
			{
				expression();
			}
			else if ((LA(1)==T_ID)) {
				r_value();
			}
			else if ((LA(1)==T_INT||LA(1)==T_FLOAT) && (LA(2)==T_COMMA)) {
				complex();
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_5_);
		}
	}
	
	public string  real() //throws RecognitionException, TokenStreamException
{
		string r_val="";
		
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_INT:
			{
				r_val=int_type();
				break;
			}
			case T_FLOAT:
			{
				r_val=float_type();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_22_);
		}
		return r_val;
	}
	
	public string  tensor() //throws RecognitionException, TokenStreamException
{
		string t_val="[";
		
		string s_val;
		
		try {      // for error handling
			if ((LA(1)==T_LSQB) && (LA(2)==T_LPAR||LA(2)==T_INT||LA(2)==T_FLOAT))
			{
				match(T_LSQB);
				s_val=scalar_s();
				match(T_RSQB);
				t_val+=s_val + "]";
			}
			else if ((LA(1)==T_LSQB) && (LA(2)==T_LSQB)) {
				match(T_LSQB);
				s_val=tensor_s();
				match(T_RSQB);
				t_val+=s_val + "]";
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_23_);
		}
		return t_val;
	}
	
	public string  list() //throws RecognitionException, TokenStreamException
{
		string l_val="{";
		
		string r_val, s_val;
		
		try {      // for error handling
			if ((LA(1)==T_LBRA) && (LA(2)==T_LPAR||LA(2)==T_INT||LA(2)==T_FLOAT) && (tokenSet_24_.member(LA(3))))
			{
				match(T_LBRA);
				s_val=scalar_s();
				match(T_RBRA);
				l_val+=s_val + "}";
			}
			else if ((LA(1)==T_LBRA) && (LA(2)==T_LSQB)) {
				match(T_LBRA);
				s_val=tensor_s();
				match(T_RBRA);
				l_val+=s_val + "}";
			}
			else if ((LA(1)==T_LBRA) && (LA(2)==T_STRING)) {
				match(T_LBRA);
				s_val=string_s();
				match(T_RBRA);
				l_val+=s_val + "}";
			}
			else if ((LA(1)==T_LBRA) && (LA(2)==T_INT||LA(2)==T_FLOAT) && (LA(3)==T_DOTDOT)) {
				match(T_LBRA);
				r_val=real();
				match(T_DOTDOT);
				s_val=real();
				l_val += r_val + ".." + s_val;
				r_val=list_r();
				l_val += r_val;
			}
			else
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_10_);
		}
		return l_val;
	}
	
	public string  scalar_s() //throws RecognitionException, TokenStreamException
{
		string ss_val="";
		
		string s_val;
		
		try {      // for error handling
			ss_val=scalar();
			{    // ( ... )*
				for (;;)
				{
					switch ( LA(1) )
					{
					case T_LPAR:
					case T_INT:
					case T_FLOAT:
					{
						s_val=scalar();
						ss_val += " " + s_val;
						break;
					}
					case T_COMMA:
					{
						match(T_COMMA);
						s_val=scalar();
						ss_val += "," + s_val;
						break;
					}
					default:
					{
						goto _loop57_breakloop;
					}
					 }
				}
_loop57_breakloop:				;
			}    // ( ... )*
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_25_);
		}
		return ss_val;
	}
	
	public string  tensor_s() //throws RecognitionException, TokenStreamException
{
		string ts_val="";
		
		string s_val="";
		
		try {      // for error handling
			ts_val=tensor();
			{    // ( ... )*
				for (;;)
				{
					switch ( LA(1) )
					{
					case T_LSQB:
					{
						s_val=tensor();
						ts_val+=" " + s_val;
						break;
					}
					case T_COMMA:
					{
						match(T_COMMA);
						s_val=tensor();
						ts_val += "," + s_val;
						break;
					}
					default:
					{
						goto _loop53_breakloop;
					}
					 }
				}
_loop53_breakloop:				;
			}    // ( ... )*
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_25_);
		}
		return ts_val;
	}
	
	public string  string_s() //throws RecognitionException, TokenStreamException
{
		string ss_val="";
		
		string s_val;
		
		try {      // for error handling
			ss_val=stringv();
			{    // ( ... )*
				for (;;)
				{
					switch ( LA(1) )
					{
					case T_STRING:
					{
						s_val=stringv();
						ss_val+=" "+s_val;
						break;
					}
					case T_COMMA:
					{
						match(T_COMMA);
						s_val=stringv();
						ss_val+=","+s_val;
						break;
					}
					default:
					{
						goto _loop69_breakloop;
					}
					 }
				}
_loop69_breakloop:				;
			}    // ( ... )*
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_12_);
		}
		return ss_val;
	}
	
	public string  list_r() //throws RecognitionException, TokenStreamException
{
		string l_val="";
		
		string r_val;
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_RBRA:
			{
				match(T_RBRA);
				l_val="}";
				break;
			}
			case T_COLON:
			{
				match(T_COLON);
				r_val=real();
				match(T_RBRA);
				l_val=":"+r_val+"}";
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_10_);
		}
		return l_val;
	}
	
	public string  scalar() //throws RecognitionException, TokenStreamException
{
		string s_val="";
		
		string c_val="";
		
		try {      // for error handling
			switch ( LA(1) )
			{
			case T_INT:
			case T_FLOAT:
			{
				s_val=real();
				break;
			}
			case T_LPAR:
			{
				match(T_LPAR);
				c_val=complex();
				match(T_RPAR);
				s_val="("+c_val+")";
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			 }
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_26_);
		}
		return s_val;
	}
	
	public string  int_type() //throws RecognitionException, TokenStreamException
{
		string r_val="";
		
		IToken  i_val = null;
		
		try {      // for error handling
			i_val = LT(1);
			match(T_INT);
			r_val=i_val.getText();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_22_);
		}
		return r_val;
	}
	
	public string  float_type() //throws RecognitionException, TokenStreamException
{
		string r_val="";
		
		IToken  f_val = null;
		
		try {      // for error handling
			f_val = LT(1);
			match(T_FLOAT);
			r_val=f_val.getText();
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_22_);
		}
		return r_val;
	}
	
	public string  quaternion_i() //throws RecognitionException, TokenStreamException
{
		string q_val=",";
		
		string val1, val2;
		
		try {      // for error handling
			match(T_COMMA);
			val1=int_type();
			match(T_COMMA);
			val2=int_type();
			q_val += val1 + "," + val2;
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_5_);
		}
		return q_val;
	}
	
	public string  quaternion_f() //throws RecognitionException, TokenStreamException
{
		string q_val=",";
		
		string val1, val2;
		
		try {      // for error handling
			match(T_COMMA);
			val1=float_type();
			match(T_COMMA);
			val2=float_type();
			q_val += val1 + "," + val2;
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_5_);
		}
		return q_val;
	}
	
	public void l_value() //throws RecognitionException, TokenStreamException
{
		
		IToken  id = null;
		
		try {      // for error handling
			id = LT(1);
			match(T_ID);
			
			Network.ParseState.network.ParseLValue(id.getText());
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_27_);
		}
	}
	
	public void empty() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			
			
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_1_);
		}
	}
	
	public void v_TRUE() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case K_TRUE:
				{
					match(K_TRUE);
					break;
				}
				case K_ON:
				{
					match(K_ON);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_1_);
		}
	}
	
	public void v_FALSE() //throws RecognitionException, TokenStreamException
{
		
		
		try {      // for error handling
			{
				switch ( LA(1) )
				{
				case K_FALSE:
				{
					match(K_FALSE);
					break;
				}
				case K_OFF:
				{
					match(K_OFF);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				 }
			}
		}
		catch (RecognitionException ex)
		{
			reportError(ex);
			recover(ex,tokenSet_1_);
		}
	}
	
	private void initializeFactory()
	{
	}
	
	public static readonly string[] tokenNames_ = new string[] {
		@"""<0>""",
		@"""EOF""",
		@"""<2>""",
		@"""NULL_TREE_LOOKAHEAD""",
		@"""macro""",
		@"""T_ID""",
		@"""T_LPAR""",
		@"""T_RPAR""",
		@"""T_RA""",
		@"""T_COMMA""",
		@"""T_ASSIGN""",
		@"""T_LBRA""",
		@"""T_RBRA""",
		@"""T_SEMI""",
		@"""include""",
		@"""T_PP""",
		@"""T_MM""",
		@"""T_LSQB""",
		@"""T_RSQB""",
		@"""T_COLON""",
		@"""T_STRING""",
		@"""T_INT""",
		@"""D_COMMENT""",
		@"""T_COMMENT""",
		@"""S_COMMENT""",
		@"""NULL""",
		@"""T_DOTDOT""",
		@"""T_FLOAT""",
		@"""true""",
		@"""on""",
		@"""false""",
		@"""off""",
		@"""cancel""",
		@"""backward""",
		@"""forward""",
		@"""loop""",
		@"""module""",
		@"""pause""",
		@"""palindrome""",
		@"""play""",
		@"""quit""",
		@"""step""",
		@"""stop""",
		@"""sequence""",
		@"""$ack""",
		@"""$bac""",
		@"""$dat""",
		@"""$for""",
		@"""$err""",
		@"""$imp""",
		@"""$inf""",
		@"""$int""",
		@"""$lin""",
		@"""$lre""",
		@"""$mac""",
		@"""$mes""",
		@"""$sin""",
		@"""$sre""",
		@"""$sys""",
		@"""$vin""",
		@"""$vre""",
		@"""L_AND""",
		@"""L_OR""",
		@"""L_NOT""",
		@"""L_EQ""",
		@"""L_NEQ""",
		@"""L_LEQ""",
		@"""L_GEQ""",
		@"""L_LT""",
		@"""L_GT""",
		@"""T_BAR""",
		@"""WS""",
		@"""AL""",
		@"""ALN""",
		@"""O""",
		@"""D""",
		@"""X""",
		@"""US""",
		@"""E""",
		@"""T_EXID""",
		@"""ESC"""
	};
	
	private static long[] mk_tokenSet_0_()
	{
		long[] data = { 29378608L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_0_ = new BitSet(mk_tokenSet_0_());
	private static long[] mk_tokenSet_1_()
	{
		long[] data = { 2L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_1_ = new BitSet(mk_tokenSet_1_());
	private static long[] mk_tokenSet_2_()
	{
		long[] data = { 29378610L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_2_ = new BitSet(mk_tokenSet_2_());
	private static long[] mk_tokenSet_3_()
	{
		long[] data = { 230912L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_3_ = new BitSet(mk_tokenSet_3_());
	private static long[] mk_tokenSet_4_()
	{
		long[] data = { 29382706L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_4_ = new BitSet(mk_tokenSet_4_());
	private static long[] mk_tokenSet_5_()
	{
		long[] data = { 128L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_5_ = new BitSet(mk_tokenSet_5_());
	private static long[] mk_tokenSet_6_()
	{
		long[] data = { 11904L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_6_ = new BitSet(mk_tokenSet_6_());
	private static long[] mk_tokenSet_7_()
	{
		long[] data = { 171051008L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_7_ = new BitSet(mk_tokenSet_7_());
	private static long[] mk_tokenSet_8_()
	{
		long[] data = { 131712L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_8_ = new BitSet(mk_tokenSet_8_());
	private static long[] mk_tokenSet_9_()
	{
		long[] data = { 640L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_9_ = new BitSet(mk_tokenSet_9_());
	private static long[] mk_tokenSet_10_()
	{
		long[] data = { 139904L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_10_ = new BitSet(mk_tokenSet_10_());
	private static long[] mk_tokenSet_11_()
	{
		long[] data = { 29378592L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_11_ = new BitSet(mk_tokenSet_11_());
	private static long[] mk_tokenSet_12_()
	{
		long[] data = { 4096L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_12_ = new BitSet(mk_tokenSet_12_());
	private static long[] mk_tokenSet_13_()
	{
		long[] data = { 139264L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_13_ = new BitSet(mk_tokenSet_13_());
	private static long[] mk_tokenSet_14_()
	{
		long[] data = { 30571186L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_14_ = new BitSet(mk_tokenSet_14_());
	private static long[] mk_tokenSet_15_()
	{
		long[] data = { 1024L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_15_ = new BitSet(mk_tokenSet_15_());
	private static long[] mk_tokenSet_16_()
	{
		long[] data = { 171051072L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_16_ = new BitSet(mk_tokenSet_16_());
	private static long[] mk_tokenSet_17_()
	{
		long[] data = { 262656L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_17_ = new BitSet(mk_tokenSet_17_());
	private static long[] mk_tokenSet_18_()
	{
		long[] data = { 171051104L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_18_ = new BitSet(mk_tokenSet_18_());
	private static long[] mk_tokenSet_19_()
	{
		long[] data = { 137495232L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_19_ = new BitSet(mk_tokenSet_19_());
	private static long[] mk_tokenSet_20_()
	{
		long[] data = { 139776L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_20_ = new BitSet(mk_tokenSet_20_());
	private static long[] mk_tokenSet_21_()
	{
		long[] data = { 171051232L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_21_ = new BitSet(mk_tokenSet_21_());
	private static long[] mk_tokenSet_22_()
	{
		long[] data = { 204354240L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_22_ = new BitSet(mk_tokenSet_22_());
	private static long[] mk_tokenSet_23_()
	{
		long[] data = { 406144L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_23_ = new BitSet(mk_tokenSet_23_());
	private static long[] mk_tokenSet_24_()
	{
		long[] data = { 136319552L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_24_ = new BitSet(mk_tokenSet_24_());
	private static long[] mk_tokenSet_25_()
	{
		long[] data = { 266240L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_25_ = new BitSet(mk_tokenSet_25_());
	private static long[] mk_tokenSet_26_()
	{
		long[] data = { 136581696L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_26_ = new BitSet(mk_tokenSet_26_());
	private static long[] mk_tokenSet_27_()
	{
		long[] data = { 132608L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_27_ = new BitSet(mk_tokenSet_27_());
	
}
}
