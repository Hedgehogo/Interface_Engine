#include "buffer.hpp"

namespace ui {
	std::vector<std::map<std::string, std::shared_ptr<IWith>>> Buffer::objectsLevels = {1, std::map<std::string, std::shared_ptr<IWith>>{}};
	
	std::map<std::string, std::shared_ptr<IWith>>& Buffer::getObjects() {
		return objectsLevels[objectsLevels.size() - 1];
	}
	
	void Buffer::raiseNestingLevel() {
		objectsLevels.emplace_back();
	}
	
	void Buffer::lowerNestingLevel() {
		objectsLevels.pop_back();
	}
	
	void Buffer::readLevel(std::function<void()> function) {
		objectsLevels.emplace_back();
		function();
		objectsLevels.pop_back();
	}
	
	bool Buffer::existObject(const std::string &name) {
		return getObjects().find(name) != getObjects().end();
	}
	
	bool Buffer::existObject(const YAML::Node &node) {
		std::string name;
		if(node.IsScalar()) {
			node >> name;
		} else {
			node["name"] >> name;
		}
		for(auto& level: objectsLevels) {
			if(level.find(name) != level.end())
				return true;
		}
		return false;
	}
}
