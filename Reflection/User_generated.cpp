#include "User.h"
RObject const* GetClassImpl(ClassTag<User>)
{
	static RObject s_Object(2);

	s_Object.fields[0].type = GetType<std::string>();
	s_Object.fields[0].name = "name\0";
	s_Object.fields[0].offset = offsetof(User,name);
	s_Object.fields[1].type = GetType<int32_t>();
	s_Object.fields[1].name = "age\0";
	s_Object.fields[1].offset = offsetof(User,age);
	return &s_Object;
}
