#pragma once

#include "general/yamlBuilder.hpp"
#include "../buffer/buffer.hpp"

namespace ui {
	template<typename Type>
	bool buildOrProcess(const YAML::Node& node, Type*& object);
	
	template<typename T>
	bool loadFromYamlFile(const YAML::Node& node, T*& object);
	
	template<typename T>
	bool loadFromYamlIf(const YAML::Node& node, T*& object);
	
	template<typename T>
	bool loadFromYamlObject(const YAML::Node& node, T*& object);
	
	template<typename T>
	T* loadFromYaml(std::string filePath);
}

#include "yamlBuilder.inl"