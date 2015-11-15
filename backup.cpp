//#include <iostream>
//#include <cstdlib>
//#include <fstream>
//#include <string>
//#include <map>
//
//using namespace std;
//
//enum TokenType {
//	T_IDENT,
//	T_KEYWORD,
//	T_CHARCONST,
//	T_STRINGCONST,
//	T_CLASS,
//	T_PUNCTUATION,
//	T_NONE,
//	T_EOF,
//};
//
//TokenType getToken(istream *, string&);
//void removeComment(istream *); //will remove the comments
//TokenType keyword(string);
//void skipLine(istream *); //will remove the line starting #
//bool notLetter(char);
//int main(int argc, char *argv[])
//{
//	if (argc > 2)											//stop if to many args
//	{
//		cout << "You entered to many arguments" << endl;
//		return 0;
//	}
//	if (argc == 1)											//stop if no args
//	{
//		cout << "You did not enter any command lines" << endl;
//		return 0;
//	}
//
//	ifstream myFile;										//declare the stream variable
//	string filename = argv[1];								//set the file name 
//	filename = filename.c_str();							//convert to c str for afs compiler
//	myFile.open(filename);									//open file to read
//	if (!myFile.is_open())									//check if it opened, if not then
//	{
//		cout << "File does not exist" << endl;				//file doesnt exist and exit
//		return 0;
//	}
//
//	map<TokenType, int> counters;							//create a map to keep track of data.	
//	map<TokenType, string> printable;
//
//	string recognized;										//recognized is the element being checked for token
//	TokenType cur;											//will hold the current token type
//	while (!myFile.eof())									//while the file isnt ended
//	{
//		cur = getToken(&myFile, recognized);				//get a token
//		if (recognized == "none")
//			continue;
//		cout << recognized << endl;							//see what was the token
//		counters[cur]++;									//else increment
//		printable[cur] = recognized;
//	}
//	cout << "out of loop";
//	map<TokenType, int>::iterator it;					//itterate through the map
//
//	for (it = counters.begin(); it != counters.end(); it++)
//	{
//		cout << printable[it->first] << ":" << it->second << endl;
//	}
//
//	myFile.close();											//close file
//	cout << "end of prog" << endl;							//debuging purpose
//
//	system("pause");
//	return 0;
//}
//
//
//TokenType getToken(istream* in, string& recognized)
//{
//	string word = "";								//temp variable
//	if (in->eof())									//if its end of file exit and notify main
//	{
//		return TokenType::T_EOF;
//	}
//	char ch = (char)in->get();						//get first character.
//	if (ch == ' ' || ch == '\n' || ch == '\t')		//if the char is a blank space
//	{
//		while (ch == ' ' || ch == '\n' || ch == '\t') //while ch is blank space, get new char
//		{
//			ch = in->get();
//		}
//	}
//	if (ch == '#')									//if char is a #, ignore the whole line
//	{
//		skipLine(in);								//skip the line
//		recognized = "none";
//		return TokenType::T_NONE;
//	}
//	if (ch == '/')									//if char is a /
//	{
//		if ((char)in->peek() == '/')				//check if its a single line
//		{
//			skipLine(in);							//if so then remove line
//		}
//		if ((char)in->peek() == '*')				//else is it a c style?
//		{
//			removeComment(in);						//if so skip the whole c style comment
//		}
//		recognized = "none";
//		return TokenType::T_NONE;
//	}
//	if (ch == '"')
//	{
//		do{
//			ch = (char)in->get();
//			word += ch;
//			if (ch == '\\' && (char)in->peek() == '"')
//				continue;
//		} while (ch != '"');
//		recognized = "none";
//		return TokenType::T_STRINGCONST;
//	}
//
//if (ch == '\'')
//{
//	do{
//		ch = (char)in->get();
//		word += ch;
//		if (ch == '\\' && (char)in->peek() == '\'')
//			continue;
//	} while (ch != '\'');
//	return TokenType::T_CHARCONST;
//}
//
//
//	if (notLetter(ch))								//if its not a letter then it must be a punctuation
//	{
//		//cout << "not letter" << endl;
//		recognized = ch;
//		while (notLetter(in->peek()) && !(in->peek() == ' ' || in->peek() == '\t' || in->peek() == '\n' || !in->eof()))
//		{
//			word += ch;
//			ch = (char)in->get();
//		}
//		return TokenType::T_PUNCTUATION;
//	}
//	word = ch;
//	while ((char)in->peek() != '\n' && !in->eof() && in->peek() != 32 && (char)in->peek() != ';')
//	{
//		ch = (char)in->get();
//		word += ch;
//	}
//	recognized = word;
//
//	TokenType keywordTest = keyword(word);
//	if (keywordTest != TokenType::T_NONE)
//	{
//		return keywordTest;
//	}
//	cout << "shit";
//	return TokenType::T_IDENT;
//}
//
//TokenType keyword(string word)
//{
//	string reservedWords[] = { "__abstract", "__alignof", "Operator", "__asm", "__assume", "__based", "__box", "__cdecl", "__declspec", "__delegate", "__event", "__except", "__fastcall", "__finally", "__forceinline", "__gc", "__hook", "__identifier", "__if_exists", "__if_not_exists", "__inline", "__int16", "__int32", "__int64", "__int8", "__interface", "__leave", "__m128", "__m128d", "__m128i", "__m64", "__multiple_inheritance", "__nogc", "__noop", "__pin", "__property", "__raise", "__sealed", "__single_inheritance", "__stdcall", "__super", "__thiscall", "__try", "__except", "__try", "__finally", "__try_cast", "__unaligned", "__unhook", "__uuidof", "__value", "__virtual_inheritance", "__w64", "__wchar_t", "wchar_t", "abstract", "array", "auto", "bool", "break", "case", "catch", "char", "class", "const", "const_cast", "continue", "decltype", "default", "delegate", "delete", "deprecated", "dllexport", "dllimport", "do", "double", "dynamic_cast", "else", "enum", "enum", "class", "enum", "struct", "event", "explicit", "extern", "false", "finally", "float", "for", "each", "in", "friend", "friend_as", "gcnew", "generic", "goto", "if", "initonly", "inline", "int", "interface", "class", "interface", "struct", "interior_ptr", "literal", "long", "mutable", "naked", "namespace", "new", "new", "noinline", "noreturn", "nothrow", "novtable", "nullptr", "operator", "private", "property", "protected", "public", "ref", "class", "ref", "struct", "register", "reinterpret_cast", "return", "safecast", "sealed", "selectany", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread", "throw", "true", "try", "typedef", "typeid", "typeid", "typename", "union", "unsigned", "using", "uuid", "value", "class", "value", "struct", "virtual", "void", "volatile", "while" };
//	for (int i = 0; i < 163; i++)
//	{
//		if (word == reservedWords[i])
//		{
//			i += 8;
//			return static_cast<TokenType>(i);
//		}
//	}
//	return TokenType::T_NONE;
//}
//
//void removeComment(istream *in)
//{
//	while (!((char)in->get() == '*' && (char)in->peek() == '/'))
//	{
//		if (in->eof())
//		{
//			cout << "unexpected end of file" << endl;
//			break;
//		}
//		if ((char)in->peek() != '*')
//		{
//			in->get();
//		}
//	}
//}
//
//void skipLine(istream *in)
//{
//	while ((char)in->peek() != '\n')
//		in->get();
//	in->get();
//}
//
//bool notLetter(char letter)
//{
//	if (!((((int)letter >= 65) && ((int)letter <= 90)) || (((int)letter >= 97) && ((int)letter <= 122))))
//	{
//		return true;
//	}
//	if (letter == '"' || letter == '\'')
//		return true;
//	return false;
//}