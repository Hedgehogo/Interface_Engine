#include "ObjectBuffer.hpp"

namespace ie {
	std::map<std::string, const YAML::Node> ObjectBuffer::nodes_ = {};
	
	void ObjectBuffer::add(const std::string& name, const YAML::Node& node) {
		nodes_.emplace(name, node);
	}
	
	bool ObjectBuffer::has(const std::string& name) {
		return nodes_.find(name) != nodes_.end();
	}
	
	const YAML::Node& ObjectBuffer::get(std::string name) {
		return nodes_[name];
	}
}