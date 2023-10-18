#pragma once

#include "IYamlBuilder/YamlBuilder/YamlBuilder.hpp"
#include "../buffer/Buffer.hpp"

namespace ie {
	template<typename Type>
	bool build_or_process(const YAML::Node& node, Type*& object);
	
	template<typename T>
	bool load_from_yaml_file(const YAML::Node& node, T*& object);
	
	template<typename T>
	bool load_from_yaml_if(const YAML::Node& node, T*& object);
	
	template<typename T>
	bool load_from_yaml_object(const YAML::Node& node, T*& object);
	
	template<typename T>
	T* load_from_yaml(std::string file_path);
}

#include "yaml-builder.inl"