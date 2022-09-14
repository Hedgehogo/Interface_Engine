//
// Created by r1n0ku on 9/14/22.
//

#include "objectBuffer.hpp"

namespace ui
{
	std::map<std::string, IObject*> ObjectBuffer::objects = {};
	void ObjectBuffer::add(std::string name, IObject *object)
	{
		objects[name] = object;
	}

	bool ObjectBuffer::has(std::string name)
	{
		return objects.find( name ) != objects.end();
	}
} // ui