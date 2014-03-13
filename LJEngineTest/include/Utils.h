#ifndef UTILS_H
#define UTILS_H
#include "LJMath.h"
#include "LJMesh.h"
#include "LJMaterial.h"
#include "LJRenderState.h"
#include <vector>
using namespace ljm;
UINT LoadShaders(const char* vertexShaderFile, const char* fragmentShaderFile);

bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<vec3f> & vertices,
	std::vector<vec2f> & uvs,
	std::vector<vec3f> & normals
);

bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<float> & vertices,
	std::vector<float> & uvs,
	std::vector<float> & normals
);

void convertToIndexedBuffer(std::vector<vec3f>& vertices,
							std::vector<vec2f>& uvs,
							std::vector<vec3f>& normals,
							std::vector<unsigned short>& indices,
							std::vector<vec3f>& indexedVertices,
							std::vector<vec2f>& indexedUvs,
							std::vector<vec3f>& indexedNormals);
void genTangents(const std::vector<vec3f>& vertices,
				 std::vector<vec2f>& uvs,
				 std::vector<vec3f>& normals,
				 std::vector<unsigned short>& indices,
				 std::vector<vec4f>& outTangents);


LJMesh* LoadMode(const char* file);

void SetMaterialToDefault(LJMaterial& mat);
#endif