#include <iostream>
#include "objloader.h"
#include "model.h"

int main(int _argc,char *argv[])
{
	objloader *loader = new objloader();
	Model pModel;

	if ((loader->ImportModel(&pModel, "test.txt")) != 0)
		exit(-3);

    std::cout << sizeof(pModel) << std::endl;
	system("pause");
	delete loader;
	return 0;
}
