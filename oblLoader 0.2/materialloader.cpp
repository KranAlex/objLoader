#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <functional>
#include "materialloader.h"
#include "Data.h"
#include "model.h"

MaterialLoader::MaterialLoader()
{

};

MaterialLoader::~MaterialLoader()
{
    fclose(m_pFile);
}

std::vector<Material> MaterialLoader::ReadMaterialFile(const char *_fname,struct Material& pMaterial)
{
    Material mater = pMaterial;
    char strline[255];
    char ch = 0;

    if (!_fname) exit(1); //WTF?

    m_pFile = fopen(_fname, "rb");

	if (!m_pFile)
	{
		exit(-2);
	}

    while (!feof(m_pFile))
    {
        ch = fgetc(m_pFile);
        //printf("%c\n", ch);
        switch (ch)
        {
        case '#':
            fgets(strline,100, m_pFile);
            break;
        case 'N':
            printf("N\n");
            ReadNs(pMaterial);
            //ReadNs();
            break;
        case 'n':
            ch = fgetc(m_pFile);
            if (ch == 'e')
            {
                while (ch != ' ') ch = fgetc(m_pFile);
                ReadNewMaterial(pMaterial);
            }
            fgets(strline,100, m_pFile);
            break;
        case 'd':
            ReadTranspar(pMaterial);
            fgets(strline,100, m_pFile);
            break;
        case 'T':
            ReadTranspar(pMaterial);
            fgets(strline, 100, m_pFile);
        case '\n':
            fgets(strline,100, m_pFile);
            break;
        default:
            fgets(strline, 100, m_pFile);
            printf("%s\n", strline);
        }
    }
    m_pMaterial.push_back(mater);
    return m_pMaterial;
}

void MaterialLoader::ReadNs(struct Material& mater)
{
    char ch;
    char strline[250];
    ch = fgetc(m_pFile);
    //fgets(strline,50,m_pFile);
    //printf("%s",strline);
    //float specular = 0.0;
    if (ch == 's')
    {
        printf("Ns\n");
        //ReadNs(pMaterial);
        fscanf(m_pFile, "%f", &mater.SpecularReflectance);
        //pMaterial->SpecularReflectance = std::move(spec);
        //printf("%f", mater.SpecularReflectance);

        fgets(strline, 100, m_pFile);
    }
    else if (ch == 'i')
    {
        printf("i\n");
    }
}

void MaterialLoader::ReadTranspar(struct Material &mater)
{
    fscanf(m_pFile, "%f", &mater.Transparency);
    //printf("transpar\n");
}

void MaterialLoader::ReadNewMaterial(struct Material &_mater)
{
    //memset(pMaterial->nameMtl, 0, sizeof(pMaterial->nameMtl));
    Material material = _mater;
    char lineName[250];
    fscanf(m_pFile, "%s", lineName);
    strcpy(material.nameMtl, lineName);
    printf("%s\n", material.nameMtl);
}
