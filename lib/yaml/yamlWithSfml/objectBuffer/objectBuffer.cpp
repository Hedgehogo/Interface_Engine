#include "objectBuffer.hpp"

namespace ui
{
	std::map<std::string, const YAML::Node> ObjectBuffer::nodes = {};
	
	void ObjectBuffer::add(const std::string& name, const YAML::Node& node) {
		nodes.emplace(name, node);
	}

	bool ObjectBuffer::has(const std::string& name) {
		return nodes.find( name ) != nodes.end();
	}
	
	const YAML::Node& ObjectBuffer::get(std::string name) {
		return nodes[name];
	}
}