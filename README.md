# Reflection
I've created a simple project to understand the core principles of a Reflection System in C++. This reflection system is not intended to be used in a real project 
but it's just a proof of concept. It contains the bare minimum to run a simple example that use reflection and to avoid that tons of line of code can distract from the 
core concept. It currently can be used only to reflect string and int32_t types and the custom parser is very inefficient and makes a lot of assumptions, but still the solution can provide some insights of the entire flow and I believe it's easy to understand.

The Visual Studio solution contains two projects **Precompiler** and **Reflection**. The first one is a simple parser that generate some necessaries *.cpp* and *.h* files, whereas the second contains the core classes of the for the reflection system and some usage examples.
Every time we compile the **Reflection** project before compiling the **Precompiler** project is build and executed generating some new files (*\*_generated.h*) that will be used during the compilation. 

## Example on how it works ?
Inside the **Reflection** project it is possible to find a test class called **User** to expose a class and its properties to the reflection 
system is sufficient to mark the class and the properties with the macros **CLASS(x)** and **PROPERTY(x)** and include the *#include "[class_file_name]_generated.h"*.

```
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
```

We can now use our reflected class in this way
```
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
```

Obtaining something like this:
```
name: string    - value: alice
age: int        - value: 24
name: string    - value: bob
age: int        - value: 32
```

## Where I took the inspiration
The best resource I've found is this video on youtube https://www.youtube.com/watch?v=XoYVeduK4yI&t=1341s the author explains very well how to approach reflection and I highly suggest to watch and follow his tutorial rather then my code :)
