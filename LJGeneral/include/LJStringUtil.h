#ifndef LJSTRINGUTIL_H
#define LJSTRINGUTIL_H

#include "LJGeneralHeaders.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

typedef vector<string> WORDS;
typedef vector<string> LINES;

class _LJExport LJStringUtil
{
	static int GetWhole(const string& str, int start, int end);
	static float GetFraction(const string& str, int start, int end);
public:
	static bool IsWhiteSpace(char c);
	static WORDS Split(const string& line);
	static int StrToInt(const string& str);
	static float StrToFloat(const string& str);
};//~LJStringUtil

class LJStringTokenizer
{
	string m_Str;
	string m_Delim;
	string::size_type m_nBegin;
	string::size_type m_nEnd;
public:
	LJStringTokenizer(const string& str, const char* delim);
	bool HasTokens();
	string NextToken();
};//~LJStringTokenizer

#endif
