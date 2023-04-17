#include <iostream>
#include <vector>

#include "User.h"

int main()
{
	// Create some users
	std::vector<User> users{ User("alice", 24), User("bob", 32) };
	// Get the static class to know how data are stored
	RObject const *userStaticClass = GetClassImpl(ClassTag<User>());
	// Inspect the classes
	for (const User& user : users)
	{
		for (auto i = 0; i < userStaticClass->fields_num; ++i)
		{
			const auto field = userStaticClass->fields[i];
			const void* valptr = static_cast<const char*>(static_cast<const void*>(&user)) + field.offset;
			
			std::cout << field.name << ": " << field.type->name;
			std::cout << "\t- value: " << TypeValueToString(field.type->name, valptr) << std::endl;
		}
	}
	return 0;
}
