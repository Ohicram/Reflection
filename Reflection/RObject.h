#pragma once

#include "Field.h"
#define CLASS(x) class x
#define PROPERTY(x) x

template<typename T>
class ClassTag {};

struct RObject
{
	Field* fields;
	RObject(size_t size) : fields_num(size)
	{
		fields = new Field[fields_num];
	}
	~RObject()
	{
		delete[] fields;
	}
	size_t fields_num;
};
