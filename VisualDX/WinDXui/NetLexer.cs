// $ANTLR 2.7.6 (2005-12-22): "netcs.g" -> "NetLexer.cs"$


namespace WinDX.UI
{
	// Generate header specific to lexer CSharp file
	using System;
	using Stream                          = System.IO.Stream;
	using TextReader                      = System.IO.TextReader;
	using Hashtable                       = System.Collections.Hashtable;
	using Comparer                        = System.Collections.Comparer;
	
	using TokenStreamException            = antlr.TokenStreamException;
	using TokenStreamIOException          = antlr.TokenStreamIOException;
	using TokenStreamRecognitionException = antlr.TokenStreamRecognitionException;
	using CharStreamException             = antlr.CharStreamException;
	using CharStreamIOException           = antlr.CharStreamIOException;
	using ANTLRException                  = antlr.ANTLRException;
	using CharScanner                     = antlr.CharScanner;
	using InputBuffer                     = antlr.InputBuffer;
	using ByteBuffer                      = antlr.ByteBuffer;
	using CharBuffer                      = antlr.CharBuffer;
	using Token                           = antlr.Token;
	using IToken                          = antlr.IToken;
	using CommonToken                     = antlr.CommonToken;
	using SemanticException               = antlr.SemanticException;
	using RecognitionException            = antlr.RecognitionException;
	using NoViableAltForCharException     = antlr.NoViableAltForCharException;
	using MismatchedCharException         = antlr.MismatchedCharException;
	using TokenStream                     = antlr.TokenStream;
	using LexerSharedInputState           = antlr.LexerSharedInputState;
	using BitSet                          = antlr.collections.impl.BitSet;
	
	public 	class NetLexer : antlr.CharScanner	, TokenStream
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
		
		public NetLexer(Stream ins) : this(new ByteBuffer(ins))
		{
		}
		
		public NetLexer(TextReader r) : this(new CharBuffer(r))
		{
		}
		
		public NetLexer(InputBuffer ib)		 : this(new LexerSharedInputState(ib))
		{
		}
		
		public NetLexer(LexerSharedInputState state) : base(state)
		{
			initialize();
		}
		private void initialize()
		{
			caseSensitiveLiterals = true;
			setCaseSensitive(true);
			literals = new Hashtable(100, (float) 0.4, null, Comparer.Default);
			literals.Add("loop", 35);
			literals.Add("$lin", 52);
			literals.Add("$for", 47);
			literals.Add("pause", 37);
			literals.Add("$mac", 54);
			literals.Add("$inf", 50);
			literals.Add("$dat", 46);
			literals.Add("step", 41);
			literals.Add("play", 39);
			literals.Add("true", 28);
			literals.Add("$lre", 53);
			literals.Add("$sin", 56);
			literals.Add("sequence", 43);
			literals.Add("$vin", 59);
			literals.Add("include", 14);
			literals.Add("on", 29);
			literals.Add("$mes", 55);
			literals.Add("$sre", 57);
			literals.Add("$ack", 44);
			literals.Add("forward", 34);
			literals.Add("$vre", 60);
			literals.Add("$imp", 49);
			literals.Add("off", 31);
			literals.Add("macro", 4);
			literals.Add("palindrome", 38);
			literals.Add("cancel", 32);
			literals.Add("backward", 33);
			literals.Add("quit", 40);
			literals.Add("$bac", 45);
			literals.Add("$int", 51);
			literals.Add("stop", 42);
			literals.Add("false", 30);
			literals.Add("$sys", 58);
			literals.Add("$err", 48);
			literals.Add("module", 36);
			literals.Add("NULL", 25);
		}
		
		override public IToken nextToken()			//throws TokenStreamException
		{
			IToken theRetToken = null;
tryAgain:
			for (;;)
			{
				IToken _token = null;
				int _ttype = Token.INVALID_TYPE;
				resetText();
				try     // for char stream error handling
				{
					try     // for lexical error handling
					{
						switch ( cached_LA1 )
						{
						case '&':
						{
							mL_AND(true);
							theRetToken = returnToken_;
							break;
						}
						case '(':
						{
							mT_LPAR(true);
							theRetToken = returnToken_;
							break;
						}
						case ')':
						{
							mT_RPAR(true);
							theRetToken = returnToken_;
							break;
						}
						case '{':
						{
							mT_LBRA(true);
							theRetToken = returnToken_;
							break;
						}
						case '}':
						{
							mT_RBRA(true);
							theRetToken = returnToken_;
							break;
						}
						case '[':
						{
							mT_LSQB(true);
							theRetToken = returnToken_;
							break;
						}
						case ']':
						{
							mT_RSQB(true);
							theRetToken = returnToken_;
							break;
						}
						case ',':
						{
							mT_COMMA(true);
							theRetToken = returnToken_;
							break;
						}
						case ':':
						{
							mT_COLON(true);
							theRetToken = returnToken_;
							break;
						}
						case ';':
						{
							mT_SEMI(true);
							theRetToken = returnToken_;
							break;
						}
						case '\t':  case '\n':  case '\r':  case ' ':
						{
							mWS(true);
							theRetToken = returnToken_;
							break;
						}
						case '@':  case 'A':  case 'B':  case 'C':
						case 'D':  case 'E':  case 'F':  case 'G':
						case 'H':  case 'I':  case 'J':  case 'K':
						case 'L':  case 'M':  case 'N':  case 'O':
						case 'P':  case 'Q':  case 'R':  case 'S':
						case 'T':  case 'U':  case 'V':  case 'W':
						case 'X':  case 'Y':  case 'Z':  case '_':
						case 'a':  case 'b':  case 'c':  case 'd':
						case 'e':  case 'f':  case 'g':  case 'h':
						case 'i':  case 'j':  case 'k':  case 'l':
						case 'm':  case 'n':  case 'o':  case 'p':
						case 'q':  case 'r':  case 's':  case 't':
						case 'u':  case 'v':  case 'w':  case 'x':
						case 'y':  case 'z':
						{
							mT_ID(true);
							theRetToken = returnToken_;
							break;
						}
						case '?':
						{
							mT_EXID(true);
							theRetToken = returnToken_;
							break;
						}
						case '"':
						{
							mT_STRING(true);
							theRetToken = returnToken_;
							break;
						}
						case '$':
						{
							mD_COMMENT(true);
							theRetToken = returnToken_;
							break;
						}
						case '#':
						{
							mT_COMMENT(true);
							theRetToken = returnToken_;
							break;
						}
						case '/':
						{
							mS_COMMENT(true);
							theRetToken = returnToken_;
							break;
						}
						default:
							if ((cached_LA1=='|') && (cached_LA2=='|'))
							{
								mL_OR(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='=') && (cached_LA2=='=')) {
								mL_EQ(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='!') && (cached_LA2=='=')) {
								mL_NEQ(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='<') && (cached_LA2=='=')) {
								mL_LEQ(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='>') && (cached_LA2=='=')) {
								mL_GEQ(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='+') && (cached_LA2=='+')) {
								mT_PP(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='-') && (cached_LA2=='-')) {
								mT_MM(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='-') && (cached_LA2=='>')) {
								mT_RA(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='!') && (true)) {
								mL_NOT(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='<') && (true)) {
								mL_LT(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='>') && (true)) {
								mL_GT(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='|') && (true)) {
								mT_BAR(true);
								theRetToken = returnToken_;
							}
							else if ((cached_LA1=='=') && (true)) {
								mT_ASSIGN(true);
								theRetToken = returnToken_;
							}
							else if ((tokenSet_0_.member(cached_LA1)) && (true)) {
								mT_INT(true);
								theRetToken = returnToken_;
							}
						else
						{
							if (cached_LA1==EOF_CHAR) { uponEOF(); returnToken_ = makeToken(Token.EOF_TYPE); }
				else {throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());}
						}
						break; }
						if ( null==returnToken_ ) goto tryAgain; // found SKIP token
						_ttype = returnToken_.Type;
						_ttype = testLiteralsTable(_ttype);
						returnToken_.Type = _ttype;
						return returnToken_;
					}
					catch (RecognitionException e) {
							throw new TokenStreamRecognitionException(e);
					}
				}
				catch (CharStreamException cse) {
					if ( cse is CharStreamIOException ) {
						throw new TokenStreamIOException(((CharStreamIOException)cse).io);
					}
					else {
						throw new TokenStreamException(cse.Message);
					}
				}
			}
		}
		
	public void mL_AND(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_AND;
		
		match("&&");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_OR(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_OR;
		
		match("||");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_NOT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_NOT;
		
		match("!");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_EQ(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_EQ;
		
		match("==");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_NEQ(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_NEQ;
		
		match("!=");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_LEQ(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_LEQ;
		
		match("<=");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_GEQ(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_GEQ;
		
		match(">=");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_LT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_LT;
		
		match("<");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mL_GT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = L_GT;
		
		match(">");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_BAR(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_BAR;
		
		match("|");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_LPAR(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_LPAR;
		
		match("(");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_RPAR(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_RPAR;
		
		match(")");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_LBRA(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_LBRA;
		
		match("{");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_RBRA(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_RBRA;
		
		match("}");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_LSQB(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_LSQB;
		
		match("[");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_RSQB(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_RSQB;
		
		match("]");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_ASSIGN(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_ASSIGN;
		
		match("=");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_COMMA(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_COMMA;
		
		match(",");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_COLON(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_COLON;
		
		match(":");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_SEMI(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_SEMI;
		
		match(";");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_PP(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_PP;
		
		match("++");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_MM(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_MM;
		
		match("--");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_RA(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_RA;
		
		match("->");
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mWS(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = WS;
		
		{
			switch ( cached_LA1 )
			{
			case ' ':
			{
				match(' ');
				break;
			}
			case '\t':
			{
				match('\t');
				break;
			}
			case '\n':
			{
				match('\n');
				if (0==inputState.guessing)
				{
					newline();
				}
				break;
			}
			case '\r':
			{
				match('\r');
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		if (0==inputState.guessing)
		{
			_ttype = Token.SKIP;
		}
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mAL(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = AL;
		
		{
			switch ( cached_LA1 )
			{
			case 'a':  case 'b':  case 'c':  case 'd':
			case 'e':  case 'f':  case 'g':  case 'h':
			case 'i':  case 'j':  case 'k':  case 'l':
			case 'm':  case 'n':  case 'o':  case 'p':
			case 'q':  case 'r':  case 's':  case 't':
			case 'u':  case 'v':  case 'w':  case 'x':
			case 'y':  case 'z':
			{
				matchRange('a','z');
				break;
			}
			case 'A':  case 'B':  case 'C':  case 'D':
			case 'E':  case 'F':  case 'G':  case 'H':
			case 'I':  case 'J':  case 'K':  case 'L':
			case 'M':  case 'N':  case 'O':  case 'P':
			case 'Q':  case 'R':  case 'S':  case 'T':
			case 'U':  case 'V':  case 'W':  case 'X':
			case 'Y':  case 'Z':
			{
				matchRange('A','Z');
				break;
			}
			case '_':
			{
				match('_');
				break;
			}
			case '@':
			{
				match('@');
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mALN(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = ALN;
		
		{
			switch ( cached_LA1 )
			{
			case 'a':  case 'b':  case 'c':  case 'd':
			case 'e':  case 'f':  case 'g':  case 'h':
			case 'i':  case 'j':  case 'k':  case 'l':
			case 'm':  case 'n':  case 'o':  case 'p':
			case 'q':  case 'r':  case 's':  case 't':
			case 'u':  case 'v':  case 'w':  case 'x':
			case 'y':  case 'z':
			{
				matchRange('a','z');
				break;
			}
			case 'A':  case 'B':  case 'C':  case 'D':
			case 'E':  case 'F':  case 'G':  case 'H':
			case 'I':  case 'J':  case 'K':  case 'L':
			case 'M':  case 'N':  case 'O':  case 'P':
			case 'Q':  case 'R':  case 'S':  case 'T':
			case 'U':  case 'V':  case 'W':  case 'X':
			case 'Y':  case 'Z':
			{
				matchRange('A','Z');
				break;
			}
			case '_':
			{
				match('_');
				break;
			}
			case '@':
			{
				match('@');
				break;
			}
			case '0':  case '1':  case '2':  case '3':
			case '4':  case '5':  case '6':  case '7':
			case '8':  case '9':
			{
				matchRange('0','9');
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mO(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = O;
		
		matchRange('0','7');
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mD(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = D;
		
		matchRange('0','9');
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mX(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = X;
		
		{
			switch ( cached_LA1 )
			{
			case '0':  case '1':  case '2':  case '3':
			case '4':  case '5':  case '6':  case '7':
			case '8':  case '9':
			{
				matchRange('0','9');
				break;
			}
			case 'a':  case 'b':  case 'c':  case 'd':
			case 'e':  case 'f':
			{
				matchRange('a','f');
				break;
			}
			case 'A':  case 'B':  case 'C':  case 'D':
			case 'E':  case 'F':
			{
				matchRange('A','F');
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mUS(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = US;
		
		{
			switch ( cached_LA1 )
			{
			case '-':
			{
				match('-');
				break;
			}
			case '+':
			{
				match('+');
				break;
			}
			case '0':  case '1':  case '2':  case '3':
			case '4':  case '5':  case '6':  case '7':
			case '8':  case '9':
			{
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mE(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = E;
		
		{
			switch ( cached_LA1 )
			{
			case 'e':
			{
				match('e');
				break;
			}
			case 'E':
			{
				match('E');
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		{
			mUS(false);
		}
		{ // ( ... )+
			int _cnt120=0;
			for (;;)
			{
				if (((cached_LA1 >= '0' && cached_LA1 <= '9')))
				{
					mD(false);
				}
				else
				{
					if (_cnt120 >= 1) { goto _loop120_breakloop; } else { throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());; }
				}
				
				_cnt120++;
			}
_loop120_breakloop:			;
		}    // ( ... )+
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_ID(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_ID;
		
		{
			mAL(false);
		}
		{    // ( ... )*
			for (;;)
			{
				if ((tokenSet_1_.member(cached_LA1)))
				{
					mALN(false);
				}
				else
				{
					goto _loop124_breakloop;
				}
				
			}
_loop124_breakloop:			;
		}    // ( ... )*
		_ttype = testLiteralsTable(_ttype);
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_EXID(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_EXID;
		
		{
			if ((cached_LA1=='?') && (tokenSet_2_.member(cached_LA2)))
			{
				match("?");
				{ // ( ... )+
					int _cnt128=0;
					for (;;)
					{
						switch ( cached_LA1 )
						{
						case '0':  case '1':  case '2':  case '3':
						case '4':  case '5':  case '6':  case '7':
						case '8':  case '9':  case '@':  case 'A':
						case 'B':  case 'C':  case 'D':  case 'E':
						case 'F':  case 'G':  case 'H':  case 'I':
						case 'J':  case 'K':  case 'L':  case 'M':
						case 'N':  case 'O':  case 'P':  case 'Q':
						case 'R':  case 'S':  case 'T':  case 'U':
						case 'V':  case 'W':  case 'X':  case 'Y':
						case 'Z':  case '_':  case 'a':  case 'b':
						case 'c':  case 'd':  case 'e':  case 'f':
						case 'g':  case 'h':  case 'i':  case 'j':
						case 'k':  case 'l':  case 'm':  case 'n':
						case 'o':  case 'p':  case 'q':  case 'r':
						case 's':  case 't':  case 'u':  case 'v':
						case 'w':  case 'x':  case 'y':  case 'z':
						{
							mALN(false);
							break;
						}
						case '?':
						{
							match("?");
							break;
						}
						default:
						{
							if (_cnt128 >= 1) { goto _loop128_breakloop; } else { throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());; }
						}
						break; }
						_cnt128++;
					}
_loop128_breakloop:					;
				}    // ( ... )+
			}
			else if ((cached_LA1=='?') && (true)) {
				match("?");
			}
			else
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			
		}
		_ttype = testLiteralsTable(_ttype);
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_INT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_INT;
		bool isDecimal=false;
		
		switch ( cached_LA1 )
		{
		case '.':
		{
			match('.');
			{
				switch ( cached_LA1 )
				{
				case '.':
				{
					match('.');
					if (0==inputState.guessing)
					{
						_ttype = T_DOTDOT;
					}
					break;
				}
				case '0':  case '1':  case '2':  case '3':
				case '4':  case '5':  case '6':  case '7':
				case '8':  case '9':
				{
					{ // ( ... )+
						int _cnt132=0;
						for (;;)
						{
							if (((cached_LA1 >= '0' && cached_LA1 <= '9')))
							{
								mD(false);
							}
							else
							{
								if (_cnt132 >= 1) { goto _loop132_breakloop; } else { throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());; }
							}
							
							_cnt132++;
						}
_loop132_breakloop:						;
					}    // ( ... )+
					{
						if ((cached_LA1=='E'||cached_LA1=='e'))
						{
							mE(false);
						}
						else {
						}
						
					}
					if (0==inputState.guessing)
					{
						_ttype = T_FLOAT;
					}
					break;
				}
				default:
					{
					}
				break; }
			}
			break;
		}
		case '+':  case '-':  case '0':  case '1':
		case '2':  case '3':  case '4':  case '5':
		case '6':  case '7':  case '8':  case '9':
		{
			mUS(false);
			{
				switch ( cached_LA1 )
				{
				case '0':
				{
					match('0');
					if (0==inputState.guessing)
					{
						isDecimal = true;
					}
					{
						switch ( cached_LA1 )
						{
						case 'X':  case 'x':
						{
							{
								switch ( cached_LA1 )
								{
								case 'x':
								{
									match('x');
									break;
								}
								case 'X':
								{
									match('X');
									break;
								}
								default:
								{
									throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
								}
								 }
							}
							{ // ( ... )+
								int _cnt138=0;
								for (;;)
								{
									if ((tokenSet_3_.member(cached_LA1)) && (true) && (true))
									{
										mX(false);
									}
									else
									{
										if (_cnt138 >= 1) { goto _loop138_breakloop; } else { throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());; }
									}
									
									_cnt138++;
								}
_loop138_breakloop:								;
							}    // ( ... )+
							break;
						}
						case '0':  case '1':  case '2':  case '3':
						case '4':  case '5':  case '6':  case '7':
						case '8':  case '9':
						{
							{ // ( ... )+
								int _cnt145=0;
								for (;;)
								{
									if (((cached_LA1 >= '0' && cached_LA1 <= '9')))
									{
										mD(false);
									}
									else
									{
										if (_cnt145 >= 1) { goto _loop145_breakloop; } else { throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());; }
									}
									
									_cnt145++;
								}
_loop145_breakloop:								;
							}    // ( ... )+
							break;
						}
						default:
							{
							}
						break; }
					}
					break;
				}
				case '1':  case '2':  case '3':  case '4':
				case '5':  case '6':  case '7':  case '8':
				case '9':
				{
					{
						matchRange('1','9');
					}
					{    // ( ... )*
						for (;;)
						{
							if (((cached_LA1 >= '0' && cached_LA1 <= '9')))
							{
								mD(false);
							}
							else
							{
								goto _loop148_breakloop;
							}
							
						}
_loop148_breakloop:						;
					}    // ( ... )*
					if (0==inputState.guessing)
					{
						isDecimal=true;
					}
					break;
				}
				default:
				{
					throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
				}
				 }
			}
			{
				if (((cached_LA1=='.'||cached_LA1=='E'||cached_LA1=='e'))&&(isDecimal))
				{
					{
						switch ( cached_LA1 )
						{
						case '.':
						{
							match('.');
							{    // ( ... )*
								for (;;)
								{
									if (((cached_LA1 >= '0' && cached_LA1 <= '9')))
									{
										mD(false);
									}
									else
									{
										goto _loop152_breakloop;
									}
									
								}
_loop152_breakloop:								;
							}    // ( ... )*
							{
								if ((cached_LA1=='E'||cached_LA1=='e'))
								{
									mE(false);
								}
								else {
								}
								
							}
							break;
						}
						case 'E':  case 'e':
						{
							mE(false);
							break;
						}
						default:
						{
							throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
						}
						 }
					}
					if (0==inputState.guessing)
					{
						_ttype = T_FLOAT;
					}
				}
				else {
				}
				
			}
			break;
		}
		default:
		{
			throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
		}
		 }
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_STRING(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_STRING;
		
		match('"');
		{    // ( ... )*
			for (;;)
			{
				if ((cached_LA1=='\\'))
				{
					mESC(false);
				}
				else if ((tokenSet_4_.member(cached_LA1))) {
					{
						match(tokenSet_4_);
					}
				}
				else
				{
					goto _loop157_breakloop;
				}
				
			}
_loop157_breakloop:			;
		}    // ( ... )*
		match('"');
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	protected void mESC(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = ESC;
		
		match('\\');
		{
			switch ( cached_LA1 )
			{
			case 'n':
			{
				match('n');
				break;
			}
			case 'r':
			{
				match('r');
				break;
			}
			case 't':
			{
				match('t');
				break;
			}
			case 'b':
			{
				match('b');
				break;
			}
			case 'f':
			{
				match('f');
				break;
			}
			case '"':
			{
				match('"');
				break;
			}
			case '\'':
			{
				match('\'');
				break;
			}
			case '\\':
			{
				match('\\');
				break;
			}
			case 'u':
			{
				{ // ( ... )+
					int _cnt161=0;
					for (;;)
					{
						if ((cached_LA1=='u'))
						{
							match('u');
						}
						else
						{
							if (_cnt161 >= 1) { goto _loop161_breakloop; } else { throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());; }
						}
						
						_cnt161++;
					}
_loop161_breakloop:					;
				}    // ( ... )+
				mX(false);
				mX(false);
				mX(false);
				mX(false);
				break;
			}
			case '0':  case '1':  case '2':  case '3':
			{
				matchRange('0','3');
				{
					if (((cached_LA1 >= '0' && cached_LA1 <= '7')) && (tokenSet_5_.member(cached_LA2)) && (true))
					{
						matchRange('0','7');
						{
							if (((cached_LA1 >= '0' && cached_LA1 <= '7')) && (tokenSet_5_.member(cached_LA2)) && (true))
							{
								matchRange('0','7');
							}
							else if ((tokenSet_5_.member(cached_LA1)) && (true) && (true)) {
							}
							else
							{
								throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
							}
							
						}
					}
					else if ((tokenSet_5_.member(cached_LA1)) && (true) && (true)) {
					}
					else
					{
						throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
					}
					
				}
				break;
			}
			case '4':  case '5':  case '6':  case '7':
			{
				matchRange('4','7');
				{
					if (((cached_LA1 >= '0' && cached_LA1 <= '7')) && (tokenSet_5_.member(cached_LA2)) && (true))
					{
						matchRange('0','7');
					}
					else if ((tokenSet_5_.member(cached_LA1)) && (true) && (true)) {
					}
					else
					{
						throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
					}
					
				}
				break;
			}
			default:
			{
				throw new NoViableAltForCharException(cached_LA1, getFilename(), getLine(), getColumn());
			}
			 }
		}
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mD_COMMENT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = D_COMMENT;
		
		match("$");
		{    // ( ... )*
			for (;;)
			{
				if ((tokenSet_5_.member(cached_LA1)))
				{
					{
						match(tokenSet_5_);
					}
				}
				else
				{
					goto _loop168_breakloop;
				}
				
			}
_loop168_breakloop:			;
		}    // ( ... )*
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mT_COMMENT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = T_COMMENT;
		
		match("#");
		{    // ( ... )*
			for (;;)
			{
				if ((tokenSet_5_.member(cached_LA1)))
				{
					{
						match(tokenSet_5_);
					}
				}
				else
				{
					goto _loop172_breakloop;
				}
				
			}
_loop172_breakloop:			;
		}    // ( ... )*
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	public void mS_COMMENT(bool _createToken) //throws RecognitionException, CharStreamException, TokenStreamException
{
		int _ttype; IToken _token=null; int _begin=text.Length;
		_ttype = S_COMMENT;
		
		match("//");
		{    // ( ... )*
			for (;;)
			{
				if ((tokenSet_5_.member(cached_LA1)))
				{
					{
						match(tokenSet_5_);
					}
				}
				else
				{
					goto _loop176_breakloop;
				}
				
			}
_loop176_breakloop:			;
		}    // ( ... )*
		if (_createToken && (null == _token) && (_ttype != Token.SKIP))
		{
			_token = makeToken(_ttype);
			_token.setText(text.ToString(_begin, text.Length-_begin));
		}
		returnToken_ = _token;
	}
	
	
	private static long[] mk_tokenSet_0_()
	{
		long[] data = { 288063250384289792L, 0L, 0L, 0L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_0_ = new BitSet(mk_tokenSet_0_());
	private static long[] mk_tokenSet_1_()
	{
		long[] data = { 287948901175001088L, 576460745995190271L, 0L, 0L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_1_ = new BitSet(mk_tokenSet_1_());
	private static long[] mk_tokenSet_2_()
	{
		long[] data = { -8935423135679774720L, 576460745995190271L, 0L, 0L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_2_ = new BitSet(mk_tokenSet_2_());
	private static long[] mk_tokenSet_3_()
	{
		long[] data = { 287948901175001088L, 541165879422L, 0L, 0L, 0L};
		return data;
	}
	public static readonly BitSet tokenSet_3_ = new BitSet(mk_tokenSet_3_());
	private static long[] mk_tokenSet_4_()
	{
		long[] data = new long[8];
		data[0]=-17179878408L;
		data[1]=-268435457L;
		for (int i = 2; i<=3; i++) { data[i]=-1L; }
		for (int i = 4; i<=7; i++) { data[i]=0L; }
		return data;
	}
	public static readonly BitSet tokenSet_4_ = new BitSet(mk_tokenSet_4_());
	private static long[] mk_tokenSet_5_()
	{
		long[] data = new long[8];
		data[0]=-9224L;
		for (int i = 1; i<=3; i++) { data[i]=-1L; }
		for (int i = 4; i<=7; i++) { data[i]=0L; }
		return data;
	}
	public static readonly BitSet tokenSet_5_ = new BitSet(mk_tokenSet_5_());
	
}
}
