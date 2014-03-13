#ifndef LJINTERTEXTUREMANAGER_H
#define LJINTERTEXTUREMANAGER_H

#include <map>
/*
 * OpenGL texture object manager
 * Used by OpenGL device to create
 * GL texture object.
 */
class LJInterTextureManager
{
public:
	typedef std::map<int, int> TEXOBJMAP;

	LJInterTextureManager();
	~LJInterTextureManager(void);
	/*
	 * Get a GL texture object by id.
	 * If succeed, the same id is returned
	 * to user. If failed, -1 is returned.
	 */
	int GetTexObj(int texId);
	/*
	 * Add a new texture object id
	 */
	void SetTexObj(int texId);
	void Clear();
private:
	TEXOBJMAP m_TexObjs;
};

#endif
