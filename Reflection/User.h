#pragma once
#include "User_generated.h"

#include <string>

CLASS(User)
{
public:
	User(std::string i_name, int32_t i_age) : name(i_name), age(i_age) {}
	
	PROPERTY(std::string name);
	PROPERTY(int32_t age);
	int32_t id;
};