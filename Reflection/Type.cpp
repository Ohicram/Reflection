#include "Type.h"
#include <sstream>

Type const* GetTypeImpl(TypeTag<int32_t>)
{
	static Type s_t{ "int", sizeof(int32_t) };
	return &s_t;
}

Type const* GetTypeImpl(TypeTag<std::string>)
{
	static Type s_t{ "string", sizeof(std::string) };
	return &s_t;
}

/* @TODO: define GetTypeImpl for all the other types
 * ...
 * ...
 */

std::string TypeValueToString(std::string TypeName, const void* VariablePtr)
{
	std::stringstream string_object_name;
	if (TypeName == "int")
	{
		string_object_name << *static_cast<const int32_t*>(VariablePtr);
	}
	else if (TypeName == "string")
	{
		const std::string strval = *static_cast<const std::string*>(VariablePtr);
		string_object_name << strval;
	}
	// @TODO: define all the other cases ...
	return string_object_name.str();
}

