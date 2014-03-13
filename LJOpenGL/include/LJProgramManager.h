#ifndef LJPROGRAMMANAGER_H
#define LJPROGRAMMANAGER_H

#include "LJGLSLProgram.h"

#include <map>
using std::map;
#include <vector>
using std::vector;
#include <string>
using std::string;
/*
 * One material one program
 */
class LJProgramManager
{
public:
	typedef map<int, int> PROGMAP;

	typedef vector<LJProgram*> PROGLIST;

	LJProgramManager();

	~LJProgramManager(void);

	LJProgram* GetProgram(int nMataterial);

	const LJProgram* GetProgram(int nMataterial)const;

	void AddProgram(int nMataterial, LJProgram *prog);
private:
	PROGMAP m_ProgMap;
	PROGLIST m_ProgList;
};//~LJProgramManager

#endif
