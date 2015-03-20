#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <cstdio>
#include <vector>
#include "model.h"
#include "Data.h"
#include "materialloader.h"

class objloader
{
public:
	objloader();
	~objloader();
	int ImportModel(Model *pModel, const char *name);
protected:
	void StartReadObject(Model *pModel);
	void ReadVertexOrVertexNormals();
	void ReadFace();
	void SaveInformAboutObject(Model *pModel,struct  Object *currentObject);
	void ComputeNormal(Model pModel);
	void CleanAll();
	void ReadMaterial();
	int PushObject(struct Object *currentObject);
private:
	FILE *m_file;
	bool m_bJustReadAFace;
	std::vector<Vector3> m_pVertex;
	std::vector<Vector3> m_pVertexNormals;
	std::vector<VectorTexture3> m_pTextCoord;
	std::vector<tFace> m_pFace;
	std::vector<Material> m_pMaterial;
    std::vector<Object> m_pObject;
};

#endif
