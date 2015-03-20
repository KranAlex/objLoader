#ifndef MATERIALLOADER_H_INCLUDED
#define MATERIALLOADER_H_INCLUDED

#include <vector>
#include <cstdio>
#include "Data.h"

class MaterialLoader
{
public:
    MaterialLoader();
    ~MaterialLoader();
    std::vector<Material> ReadMaterialFile(const char *_fname,struct Material& pMaterial);
protected:
    void ReadNewMaterial(struct Material &_mater);
    void ReadKa();
    void ReadKs();
    void ReadKd();
    void ReadNs(struct Material &mater);
    void ReadTranspar(struct Material &mater);
private:
    FILE *m_pFile;
    std::vector<Material> m_pMaterial;
};

#endif // MATERIALLOADER_H_INCLUDED
