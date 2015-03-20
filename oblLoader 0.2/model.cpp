#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <vector>
#include "model.h"
#include "objloader.h"
#include "Data.h"

Model::Model(){}

Model::~Model(){}

int Model::countOfObject()const
{
	return numOfObjects;
}
