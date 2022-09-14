#pragma once

#include "../yaml.hpp"

namespace ui
{
	class IObject;
	class ObjectBuffer
	{
	protected:
		static std::map<std::string, IObject*> objects;
	public:
		static void add(std::string name, IObject *object);

		template<typename T>
		static T* get(std::string name);

		static bool has(std::string name);
	};
}

#include "objectBuffer.inl"