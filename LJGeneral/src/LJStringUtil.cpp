#include "LJStringUtil.h"

bool LJStringUtil::IsWhiteSpace(char c)
{
	if(c == ' ' || c == '\t' || c == '\n' || c == '\r')
	{
		return true;
	}
	return false;
}

int LJStringUtil::StrToInt(const string& str)
{
	return (int)StrToFloat(str);
}

float LJStringUtil::StrToFloat(const string& str)
{
	int n = str.size();
	if(n == 0 || (str[0] == '.' && n == 1))
		throw "Invalid Value";
	bool neg = false;
	if(str[0] == '-') {
		neg = true;
	}
	string::size_type m = str.find_first_of('.');
	if(m == string::npos)
	{
		return (float)GetWhole(str, 0, n-1);
	}
	if(neg)
		return -(GetWhole(str, 0, m-1) + GetFraction(str, m+1, n-1));
	else
		return GetWhole(str, 0, m-1) + GetFraction(str, m+1, n-1);
}

string LJStringUtil::IntToStr(int n)
{
	int m = n;
	bool neg = false;
	if(n < 0)
	{
		m = -n;
		neg = true;
	}
	string str;
	do {
		str.push_back('0' + m%10);
		m /= 10;
	} while(m != 0);
	if(neg)
	{
		str.push_back('-');
	}
	string ret;
	string::iterator it = str.end();
	--it;
	while(it >= str.begin())
	{
		ret.push_back(*it);
		--it;
	}
	return ret;
}

WORDS LJStringUtil::Split(const string& line)
{
	WORDS words;
	LJStringTokenizer Toknizr(line, NULL);
	while(Toknizr.HasTokens())
	{
		words.push_back(Toknizr.NextToken());
	}
	return words;
}

//WORDS LJEffectFileParser::Split(const string& line)
//{
//	WORDS words;
//	int length = line.size();
//	int start;
//	int end;
//	for(int i = 0; i < length; ++i)
//	{
//		if(LJStringUtil::IsWhiteSpace(line[i]))
//			continue;
//		start = i;
//		// find sub-string length
//		for(int j = i+1; j < length; ++j)
//		{
//			if(LJStringUtil::IsWhiteSpace(line[j]))
//			{
//				end = j;
//				i = j;
//				break;
//			}
//		}
//		string word(line, start, end-start);
//		words.push_back(word);
//	}
//	return words;
//}

LJStringTokenizer::LJStringTokenizer(const string& str, const char *delim)
	:m_Str(str), m_nBegin(0), m_nEnd(0)
{
	if(!delim)
	{
		m_Delim = " \f\n\r\t\v";
	}
	else
	{
		m_Delim = delim;
	}
	m_nBegin = m_Str.find_first_not_of(m_Delim);
	m_nEnd = m_Str.find_first_of(m_Delim, m_nBegin);
}

bool LJStringTokenizer::HasTokens()
{
	return (m_nBegin != m_nEnd);
}

string LJStringTokenizer::NextToken()
{
	string ret;
	if(m_nBegin != string::npos && m_nEnd != string::npos)
	{
		ret = m_Str.substr(m_nBegin, m_nEnd - m_nBegin);
		m_nBegin = m_Str.find_first_not_of(m_Delim, m_nEnd);
		m_nEnd = m_Str.find_first_of(m_Delim, m_nBegin);
	}
	else if(m_nBegin != string::npos)
	{
		ret = m_Str.substr(m_nBegin, m_Str.size()-m_nBegin);
		m_nBegin = m_Str.find_first_not_of(m_Delim, m_nEnd);
	}
	return ret;
}

int LJStringUtil::GetWhole(const string& str, int start, int end)
{
	int s = 0;
	for(int i = start; i <= end; ++i)
	{
		s = s*10 + (str[i] - '0');
	}
	return s;
}

float LJStringUtil::GetFraction(const string& str, int start, int end)
{
	float s = 0;
	for(int i = end; i >= start; --i)
	{
		s = s + (str[i]-'0');
		s *= 0.1f;
	}
	return s;
}
