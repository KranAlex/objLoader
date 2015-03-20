#ifndef _DATA_H_
#define _DATA_H_

#include <Windows.h>
#include <vector>


struct Vector3
{
	float x, y, z;
};

struct VectorTexture3
{
    float u,v,w;
};

struct Vector2
{
	float x, y;
};

struct Texture
{

};

struct Material{
    char nameMtl[250];
    float SpecularReflectance;
    float Transparency;
    int Lighting;
    std::vector<Texture> m_pText;
};

struct tFace{
	int vertIndex[3];
	int coordIndex[3];
};

struct Object{
	int numOfVertex;
	int numOfFaces;
	int numTextVertex;
	int materialId;
	char nameObject[250];
	std::vector<VectorTexture3> objectTextCoord;
	std::vector<Vector3> objectVertex;
	std::vector<Vector3> objectNormals;
	std::vector<tFace> objectFace;
};

#endif
