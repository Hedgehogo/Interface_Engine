#include "buffer.hpp"

namespace ui {
	std::vector<std::map<std::string, std::shared_ptr<IWith>>> Buffer::objectsLevels = {1, std::map<std::string, std::shared_ptr<IWith>>{}};
	
	std::shared_ptr<IWith> Buffer::getAxis(const std::shared_ptr<IWith> &vector, const std::string &name) {
		std::shared_ptr<IWithVector2> vec{std::dynamic_pointer_cast<IWithVector2>(vector)};
		if(vec == nullptr) {
			throw BufferVariableNotFoundException{name, get_type<IWith>()};
		}
		if(name == "x") {
			return vec->getXPtr();
		} else if(name == "y") {
			return vec->getYPtr();
		}
		throw BufferVariableNotFoundException{name, get_type<IWith>()};
	}
	
	std::shared_ptr<IWith> Buffer::getVariable(const std::shared_ptr<IWith> &var, std::vector<std::string> &names) {
		if(!names.empty()) {
			std::string name = names[names.size() - 1];
			names.pop_back();
			if(name == "x" || name == "y") {
				return getAxis(getVariable(var,names), name);
			} else {
				throw BufferVariableNotFoundException{name, get_type<IWith>()};
			}
		}
		return var;
	}
	
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
	
	std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter) {
		std::stringstream strStream{str};
		std::vector<std::string> result;
		std::string substr;
		while(std::getline(strStream, substr, delimiter)) {
			result.push_back(substr);
		}
		return result;
	}
	
	bool Buffer::existObject(const std::string &name) {
		std::vector<std::string> names = splitByDelimiter(name, '.');
		return getObjects().find(names[0]) != getObjects().end();
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
