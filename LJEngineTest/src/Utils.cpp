#include <GL/glew.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace ljm;

GLuint LoadShaders(const char* vertexShaderFile,
				   const char* fragmentShaderFile)
{
	// Create shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Load vertex shader code
	std::string vertexSourceCode;
	std::ifstream vertexSourceStream(vertexShaderFile, std::ios::in);
	if(vertexSourceStream.is_open()) {
		std::string line = "";
		while(getline(vertexSourceStream, line)) {
			vertexSourceCode += "\n" + line;
		}
		vertexSourceStream.close();
	}

	// Load fragment shader code
	std::string fragmentSourceCode;
	std::ifstream fragmentSourceStream(fragmentShaderFile, std::ios::in);
	if(fragmentSourceStream.is_open()) {
		std::string line = "";
		while(getline(fragmentSourceStream, line)) {
			fragmentSourceCode += "\n" + line;
		}
		fragmentSourceStream.close();
	}

	// Upload shader code and compile
	const char* vertexSourcePointer = vertexSourceCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	// Check compile status
	GLint result;
	GLint logInfoLength;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &logInfoLength);
	std::vector<char> shaderErrorMessage(logInfoLength);
	if(logInfoLength != 0) {
		glGetShaderInfoLog(vertexShaderID, logInfoLength, NULL, &shaderErrorMessage[0]);
		std::cout << &shaderErrorMessage[0] << std::endl;
	}

	const char* fragmentSourcePointer = fragmentSourceCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &logInfoLength);
	if(logInfoLength != 0) {
		std::vector<char> shaderErrorMessage1(logInfoLength);
		glGetShaderInfoLog(fragmentShaderID, logInfoLength, NULL, &shaderErrorMessage1[0]);
		std::cout << &shaderErrorMessage1[0] << std::endl;
	}

	// Link the program
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logInfoLength);
	if(logInfoLength != 0) {
	std::vector<char> programErrorMessage(logInfoLength);
	glGetProgramInfoLog(programID, logInfoLength, NULL, &programErrorMessage[0]);
	std::cout << &programErrorMessage[0] << std::endl;
	}

	// delete shader
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}


bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<vec3f> & vertices,
	std::vector<vec2f> & uvs,
	std::vector<vec3f> & normals
){

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(vec3f(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(vec2f(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(vec3f(n.x, n.y, n.z));
	}


	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	
	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<float> & vertices,
	std::vector<float> & uvs,
	std::vector<float> & normals
){

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices*3);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(pos.x);
		vertices.push_back(pos.y);
		vertices.push_back(pos.z);
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices*2);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(UVW.x);
		uvs.push_back(UVW.y);
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices*3);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(n.x);
		normals.push_back(n.y);
		normals.push_back(n.z);
	}


	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	
	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

struct PackedVertex {
	vec3f v;
	vec2f u;
	vec3f n;
	bool operator<(const PackedVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};
//typedef _PackedVertex PackedVertex;

void convertToIndexedBuffer(std::vector<vec3f>& vertices,
							std::vector<vec2f>& uvs,
							std::vector<vec3f>& normals,
							std::vector<unsigned short>& indices,
							std::vector<vec3f>& indexedVertices,
							std::vector<vec2f>& indexedUvs,
							std::vector<vec3f>& indexedNormals)
{
	std::map<PackedVertex, unsigned short> cachedPV;
	int size = vertices.size();
	for(int i = 0; i < size; ++i) {
		PackedVertex pv = {vertices[i], uvs[i], normals[i]};
		std::map<PackedVertex, unsigned short>::iterator it;
		it = cachedPV.find(pv);
		if(it == cachedPV.end()) { // not cached
			indexedVertices.push_back(vertices[i]);
			indexedUvs.push_back(uvs[i]);
			indexedNormals.push_back(normals[i]);
			unsigned short index = indexedVertices.size()-1;
			indices.push_back(index);
			cachedPV[pv] = index;
		} else { // cached
			unsigned short index = it->second;
			indices.push_back(index);
		}
	}
}

void genTangents(const std::vector<vec3f>& vertices,
				 std::vector<vec2f>& uvs,
				 std::vector<vec3f>& normals,
				 std::vector<unsigned short>& indices,
				 std::vector<vec4f>& outTangents)
{
	// Gen T & B
	using namespace std;
	vector<vec3f> tangents(vertices.size());
	vector<vec3f> btangents(vertices.size());
	for(unsigned int i = 0; i < indices.size(); i += 3) {
		unsigned short i0, i1, i2;
		i0 = indices[i];
		i1 = indices[i+1];
		i2 = indices[i+2];

		vec3f v0, v1, v2;
		v0 = vertices[i0];
		v1 = vertices[i1];
		v2 = vertices[i2];

		vec2f uv0, uv1, uv2;
		uv0 = uvs[i0];
		uv1 = uvs[i1];
		uv2 = uvs[i2];

		vec3f q0, q1;
		q0 = v1-v0;
		q1 = v2-v0;
		vec2f st0, st1;
		st0 = uv1-uv0;
		st1 = uv2-uv0;

		float r = 1.0f/(st0.x*st1.y - st0.y*st1.x);
		vec3f T = r*(st1.y*q0 - st0.y*q1);
		vec3f B = r*(-st1.x*q0 + st0.x*q1);

		tangents[i0] += T;
		tangents[i1] += T;
		tangents[i2] += T;
		btangents[i0] += B;
		btangents[i1] += B;
		btangents[i2] += B;
	}

	// Gen T'
	for(unsigned int i = 0; i < vertices.size(); ++i) {
		vec3f tangent = tangents[i] - dot(normals[i], tangents[i]) * normals[i];
		tangent = normalize(tangent);
		outTangents[i] = vec4f(tangent, 1.0);
		outTangents[i].w = (dot(cross(normals[i], tangent), btangents[i]) < 0.0f) ? -1.0f : 1.0f;
	}
}

LJMesh* LoadMode(const char* file)
{
	if(!file) return NULL;

	using std::vector;

	 //--------SETUP VERTICES--------
	 vector<ljm::vec3f> verts, normals;
	 vector<ljm::vec2f> texcoords;
	 vector<unsigned short> inds;
	 if(!loadAssImp(file, inds, verts, texcoords, normals))
	 {
		 std::cout << "loadAssImp failed" << std::endl;
		 return NULL;
	 }

	 vector<ljm::vec3f> indVerts, indNormals;
	 vector<ljm::vec2f> indTexcoords;
	 vector<unsigned short> indInds;
	 convertToIndexedBuffer(verts, texcoords, normals, indInds, indVerts, indTexcoords, indNormals);

	 vector<ljm::vec4f> Tangents(indVerts.size());
	 genTangents(indVerts, indTexcoords, indNormals, indInds, Tangents);

     LJMesh *pMesh = new LJMesh();
     pMesh->SetBuffer(indVerts.data(), 3, indVerts.size()*3, LJVertexBuffer::Float,
             "inPosition", LJVertexBuffer::LJ_ARRAY_BUFFER,
             LJVertexBuffer::LJ_STATIC_DRAW);
	 pMesh->SetBuffer(indNormals.data(), 3, indNormals.size()*3, LJVertexBuffer::Float,
			 "inNormal", LJVertexBuffer::LJ_ARRAY_BUFFER,
			 LJVertexBuffer::LJ_STATIC_DRAW);
	 pMesh->SetBuffer(indTexcoords.data(), 2, indTexcoords.size()*2, LJVertexBuffer::Float,
			 "inTexcoord", LJVertexBuffer::LJ_ARRAY_BUFFER,
			 LJVertexBuffer::LJ_STATIC_DRAW);
	 pMesh->SetBuffer(Tangents.data(), 4, Tangents.size()*4, LJVertexBuffer::Float,
			 "inTangent", LJVertexBuffer::LJ_ARRAY_BUFFER,
			 LJVertexBuffer::LJ_STATIC_DRAW);
     pMesh->SetIndexBuffer(indInds.data(), indInds.size(), LJVertexBuffer::UnsignedShort,
             LJVertexBuffer::LJ_ELEMENT_ARRAY_BUFFER,
             LJVertexBuffer::LJ_STATIC_DRAW);
     pMesh->SetMode(LJMesh::LJ_TRIANGLES);

	 return pMesh;
}

void SetMaterialToDefault(LJMaterial& mat)
{
	LJMaterial *pMat0 = &mat;

	 LJRenderState renderState;
	 renderState.SetDepth(true);

     LJPass *pPas0 = new LJPass();
     pPas0->SetName("Default");
	 pPas0->SetRenderState(renderState);

	 LJTechnique pTech0;
	 pTech0.AddPass(*pPas0);
     pTech0.SetName("Default");
	 pTech0.SetCurrentPass(pPas0->GetName());

	 pMat0->AddTechnique(pTech0);
	 pMat0->SetCurrentTech(pTech0.GetName());

}
