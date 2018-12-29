#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int fd;

typedef enum tokken_kind tk;

enum tokken_kind
{
    Lparen=1, Rparen, Plus,  Minus,  Multi,  Divi,
    Assign,   Comma,  DblQ,
    Equal,    NotEq,  Less,  LessEq, Great,  GreatEq,
    If,       Else,   End,   Print,  Ident,  IntNum,
    String,   Letter, Digit, EofTkn, Others, END_list
};

typedef struct _tokken tokken;

struct _tokken
{
    tk kind;
    char text[8];
    int  intVal;
};

void init_tokken(struct _tokken *t, tk tk, char *str, int d)
{
	t->kind = tk;
	strcpy(t->text, str);
	t->intVal = d;
}

void initChTyp(void);
struct _tokken nextTkn(void);
int nextCh(void);
bool is_ope2(int c1, int c2);
tk get_kind(const char *s);
//enum tokken_kind get_kind(const string& s);

tk ctyp[256];
tokken tok;

typedef struct KeyWord kw;

struct KeyWord
{
    const char *keyName;
    tk keyKind;
};

kw KeyWdTbl[] =
{
    {"if" , If    }, {"else",  Else    },
    {"end", End   }, {"print", Print   },
    {"(",   Lparen}, {")",     Rparen  },
    {"+",   Plus  }, {"-",     Minus   },
    {"*",   Multi }, {"/",     Divi    },
    {"=",   Assign}, {",",     Comma   },
    {"==",  Equal }, {"!=",    NotEq   },
    {"<",   Less  }, {"<=",    LessEq  },
    {">",   Great }, {">=",    GreatEq },
    {"", END_list},
};

int main(int argc, char *argv[])
{
    if (argc == 1)
		exit(1);

    fd = open(argv[1], O_RDWR);

	if (!fd)
		exit(1);

	init_tokken(&tok, Others, "", 0);

	printf("text	kind	intVal\n");
    initChTyp();

    for(tok = nextTkn(); tok.kind != EofTkn; tok = nextTkn())
	{
		printf("%s\t%d\t%d\n", tok.text, tok.kind, tok.intVal);
    }

    return 0;
}

void initChTyp(void)
{
	int i;

    for(i=0; i<256; i++)
		ctyp[i] = Others;

    for(i='0'; i<='9'; i++)
		ctyp[i] = Digit;

    for(i='A'; i<='Z'; i++)
		ctyp[i] = Letter;

    for(i='a'; i<='z'; i++)
		ctyp[i] = Letter;

    ctyp['('] = Lparen;
	ctyp[')'] = Rparen;
    ctyp['<'] = Less;
	ctyp['>'] = Great;
    ctyp['+'] = Plus;
	ctyp['-'] = Minus;
    ctyp['*'] = Multi;
	ctyp['/'] = Divi;
    ctyp['_'] = Letter;
	ctyp['='] = Assign;
    ctyp[','] = Comma;
	ctyp['"'] = DblQ;
}

struct _tokken nextTkn(void)
{
	tk kd;
    int ch0, num = 0;
    static int ch = ' ';
    char txt[32] = {0};
	int cnt = 0;
	struct _tokken tokken;

    while(isspace(ch))
		ch = nextCh();

    if(ch == -1)
	{
		init_tokken(&tokken, EofTkn, txt, 0);
		return tokken;
		//return _tokken(EofTkn, txt);
	}

    switch(ctyp[ch])
	{
    	case Letter:
        	for(; ctyp[ch] == Letter || ctyp[ch] == Digit; ch = nextCh())
            	txt[cnt++] = ch;
	        break;

	    case Digit:
    	    for(num=0; ctyp[ch]==Digit; ch=nextCh())
        	     num = num * 10 + (ch - '0');

			init_tokken(&tokken, IntNum, txt, num);
			return tokken;
	        //return _tokken(IntNum, txt, num);

	    case DblQ:
    	    for(ch = nextCh(); ch != -1 && ch != '\n' && ch != '"'; ch = nextCh())
        	    txt[cnt++] = ch;

        	if (ch != '"')
			{
				printf("Char Literal Prob\n");
				exit(1);
			}

    	    ch = nextCh();
			init_tokken(&tokken, String, txt, 0);
			return tokken;
    	    //return _tokken(String, txt);

	    default:
	        txt[cnt++] = ch;
			ch0 = ch;
			ch = nextCh();

	        if(is_ope2(ch0, ch))
			{
				txt[cnt++] = ch;
				ch = nextCh();
			}
    }

    kd = get_kind(txt);

    if(kd == Others)
	{
		printf("Wrong Tokken: %s\n", txt);
		exit(1);
    }

	init_tokken(&tokken, kd, txt, 0);
	return tokken;
    //return _tokken(kd, txt);
}

int nextCh(void)
{
    static int c = 0;

    if(c == -1)
		return c;

    if((read(fd, &c, 1)) == 0)
	{
		c = -1;
		close(fd);
	}

    return c;
}

bool is_ope2(int c1, int c2)
{
    char s[] = "    ";

    if (c1=='\0' || c2=='\0')
		return false;

    s[1] = c1;
	s[2] = c2;

    return strstr(" <= >= == != ", s) != NULL;
}

tk get_kind(const char *s)
{
    for(int i=0; KeyWdTbl[i].keyKind != END_list; i++)
        if(!strncmp(s, KeyWdTbl[i].keyName, strlen(s)))
			return KeyWdTbl[i].keyKind;

#if 0
    for (int i=0; KeyWdTbl[i].keyKind != END_list; i++) {
        if (s == KeyWdTbl[i].keyName)
			return KeyWdTbl[i].keyKind;
    }
#endif

    if(ctyp[s[0]] == Letter)
		return Ident;

    if(ctyp[s[0]] == Digit)
		return IntNum;

    return Others;
}
