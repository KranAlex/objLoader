#ifndef  _MODEL_H_
#define _MODEL_H_

#include <vector>
#include "Data.h"

class Model{
public:
	Model();
	~Model();
	int numOfObjects;
	int numOfMaterial;
	int countOfObject()const;
	std::vector<Material> m_pMaterial;
	std::vector<Object> m_pObject;
};


#endif