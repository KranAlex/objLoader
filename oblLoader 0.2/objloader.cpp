#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include <iterator>
#include "model.h"
#include "objloader.h"
#include "Data.h"
#include "materialloader.h"


objloader::objloader()
{
}


objloader::~objloader()
{
	fclose(m_file);
	m_file = nullptr;
	printf("Close Objloader\n");
}

int objloader::ImportModel(Model *pModel,const char *name)
{
	if (!name) return -1;

	m_file = fopen(name , "r");

	if (m_file == NULL)
	{
		return -3;
	}

	StartReadObject(pModel);

	return 0;
}

void objloader::StartReadObject(Model *pModel)
{
    Object obj = { 0 };
    obj.materialId = 0;
	//if (!pModel) return;
	char line[250] = { 0 };
	char ch = 0;

	while (!feof(m_file))
	{
		ch = fgetc(m_file);
		switch (ch)
		{
        case '#':
            fgets(line,100,m_file);
            break;
		case 'v':
			if (!m_bJustReadAFace)
			{
				SaveInformAboutObject(pModel,&obj);
			}
			
			ReadVertexOrVertexNormals();
			break;
		case 'f':
		    ReadFace();
			break;
		case 'm':
		    ReadMaterial();
			obj.materialId++;
			break;
		case 'n':
			fgets(line, 100, m_file);
			break;
        case 'o':
            //printf("O\n");
            SaveInformAboutObject(pModel,&obj);
            // это новый объект
            //char nameObj[250];
            fscanf(m_file, "%s", obj.nameObject);
            fgets(line, 100, m_file);
            break;
		default:
			fgets(line, 100, m_file);
			break;
		}
	}
	SaveInformAboutObject(pModel,&obj);
}

void objloader::ReadVertexOrVertexNormals()
{
	VectorTexture3 tNewTextCoord = { 0 };
	Vector3 tNewVertex = { 0 };
	Vector3 tNewVertexNormals = { 0 };
	char ch = 0;
	char line[255] = { 0 };

	ch = fgetc(m_file);

	if (ch == ' ')
	{
		//читаем кординаты вершины
		fscanf(m_file, "%f %f %f", &tNewVertex.x, &tNewVertex.y, &tNewVertex.z);
		fgets(line, 100, m_file);
		m_pVertex.push_back(tNewVertex);
	}
	else if (ch == 't')
	{
		fscanf(m_file, "%f %f [%f]", &tNewTextCoord.u, &tNewTextCoord.v ,&tNewTextCoord.w);
		fgets(line, 100, m_file);
		m_pTextCoord.push_back(tNewTextCoord);
		m_bJustReadAFace = true;
	}
	else if (ch == 'n')
    {
        fscanf(m_file,"%f %f %f", &tNewVertexNormals.x, &tNewVertexNormals.y, &tNewVertexNormals.z);
        fgets(line, 100, m_file);
        m_pVertexNormals.push_back(tNewVertexNormals);
    }
	else {
		fgets(line, 100, m_file);
	}
}

void objloader::ReadFace()
{
	tFace tNewFace = { 0 };
	//char line[255] = { 0 };

	if (m_bJustReadAFace)
	{
		fscanf(m_file, "%d/%d %d/%d %d/%d", &tNewFace.vertIndex[0], &tNewFace.coordIndex[0], &tNewFace.vertIndex[1], &tNewFace.coordIndex[1],
										&tNewFace.vertIndex[2], &tNewFace.coordIndex[2]);
	}
	else {
		fscanf(m_file, "%d %d %d", &tNewFace.vertIndex[0], &tNewFace.vertIndex[1], &tNewFace.vertIndex[2]);
	}

	m_pFace.push_back(tNewFace);

	m_bJustReadAFace = true;
}

void objloader::ReadMaterial()
{
	Material pMaterial;

	char ch = 0;
	char nameMaterialFile[255];
	char line[255];

	ch = fgetc(m_file);
	if (ch == ' ')
	{
		return;				//WTF?!
	}
	else if (ch == 't')
	{
		while (ch != ' '){
			ch = fgetc(m_file);
		}
        MaterialLoader load;
		fscanf(m_file,"%s", nameMaterialFile);
		//printf("%s\n", nameMaterialFile);
        m_pMaterial = std::move(load.ReadMaterialFile(nameMaterialFile,pMaterial));
        //printf("%d", m_pMaterial.size());
        //printf("%s",m_pMaterial[0].nameMtl);
        fgets(line, 100, m_file);
        return;
	}

}

void objloader::SaveInformAboutObject(Model *pModel, Object *currentObject)
{
	if (!(PushObject(currentObject) == 0))
    {
        printf("chet ne tak");
        exit(-1);
    }
	pModel->numOfObjects = m_pObject.size();
	pModel->numOfMaterial = m_pMaterial.size();
	pModel->m_pObject = std::move(m_pObject);
	pModel->m_pMaterial = std::move(m_pMaterial);
}


int objloader::PushObject(Object *currentObject)
{
    if (currentObject == nullptr)
        return -3;

    currentObject->numOfFaces  = m_pFace.size();
	currentObject->numOfVertex = m_pVertex.size();
	currentObject->numTextVertex = m_pTextCoord.size();
	currentObject->objectVertex = std::move(m_pVertex);
	currentObject->objectNormals = std::move(m_pVertexNormals);
	currentObject->objectFace = std::move(m_pFace);
	currentObject->objectTextCoord = std::move(m_pTextCoord);

	m_pObject.push_back(*currentObject);

    return 0;
}

void objloader::CleanAll()
{
	m_pFace.clear();
	m_pTextCoord.clear();
	m_pVertex.clear();
}
