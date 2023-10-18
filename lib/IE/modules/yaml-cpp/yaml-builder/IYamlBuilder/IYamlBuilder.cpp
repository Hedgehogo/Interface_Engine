#include "IYamlBuilder.hpp"

namespace ie {
	std::string remove_namespace(std::string name, std::string name_space) {
		std::string name_space_name = name_space + std::string("::");
		if(name.size() >= name_space_name.size() && name.substr(0, name_space_name.size()) == name_space_name) {
			return name.substr(name_space_name.size());
		}
		return name;
	}
	
	namespace detail {
		IYamlBuilder::TypeNameDeformer IYamlBuilder::type_name_deform = [](std::string name) -> std::string {
			return remove_namespace(std::move(name), "ui");
		};
		
		void IYamlBuilder::set_type_name_deformer(const TypeNameDeformer& type_name_deform) {
			IYamlBuilder::type_name_deform = type_name_deform;
		}
		
		bool IYamlBuilder::is_exists() {
			return true;
		}
		
		IYamlBuilder::operator bool() {
			return is_exists();
		}
	}
	
	void set_type_name_deformer(const detail::IYamlBuilder::TypeNameDeformer& type_name_deform) {
		detail::IYamlBuilder::set_type_name_deformer(type_name_deform);
	}
}