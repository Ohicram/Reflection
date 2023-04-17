#pragma once
#include <cstdint>
#include <string>

struct Type
{
	char const* name;
	size_t size;
};

template<typename T>
class TypeTag{};

template<typename T>
Type const* GetType()
{
	return GetTypeImpl(TypeTag<T>{});
}

Type const* GetTypeImpl(TypeTag<int32_t>);

Type const* GetTypeImpl(TypeTag<std::string>);

std::string TypeValueToString(std::string TypeName, const void* VariablePtr);

// @Todo: define all other types...