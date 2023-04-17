#pragma once

#include "Type.h"

struct Field
{
	const Type* type;
	char const* name;
	size_t offset;
};
