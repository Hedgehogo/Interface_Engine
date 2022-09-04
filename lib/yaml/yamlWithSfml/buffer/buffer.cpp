#include "buffer.hpp"

namespace ui {
	std::shared_ptr<IWith> getVectorAxis(const std::shared_ptr<IWith> &vector, const std::string &name) {
		std::shared_ptr<IWithVector2> vec{std::dynamic_pointer_cast<IWithVector2>(vector)};
		if(vec == nullptr) {
			throw BufferVariableNotFoundException{name, type_name<IWith>()};
		}
		if(name == "x") {
			return vec->getXPtr();
		} else if(name == "y") {
			return vec->getYPtr();
		}
		throw BufferVariableNotFoundException{name, type_name<IWith>()};
	}
	
	std::shared_ptr<IWith> getListElement(const std::shared_ptr<IWith> &var, const std::string &name) {
		std::shared_ptr<IWithList> list{std::dynamic_pointer_cast<IWithList>(var)};
		if(list == nullptr) {
			throw BufferVariableNotFoundException{name, type_name<IWith>()};
		}
		return list->getElementPtr(std::stoull(name));
	}
	
	std::vector<std::map<std::string, std::shared_ptr<IWith>>> Buffer::objectsLevels = {1, std::map<std::string, std::shared_ptr<IWith>>{}};
	std::vector<std::pair<std::regex, Buffer::getOption>> Buffer::options = {
		std::make_pair(std::regex{R"([xy])"}, getVectorAxis),
		std::make_pair(std::regex{R"(\d+)"}, getListElement)
	};
	
	std::shared_ptr<IWith> Buffer::getVariable(const std::shared_ptr<IWith> &var, std::vector<std::string> &names) {
		if(!names.empty()) {
			std::string name = names[names.size() - 1];
			names.pop_back();
			auto optionFunction = std::find_if(options.begin(), options.end(), [&](const std::pair<std::regex, getOption>& option) {
				return std::regex_match(name.cbegin(), name.cend(), option.first);
			});
			if(optionFunction != options.end()) {
				return optionFunction->second(getVariable(var,names), name);
			} else {
				throw BufferVariableNotFoundException{name, type_name<IWith>()};
			}
		}
		return var;
	}
	
	std::map<std::string, std::shared_ptr<IWith>>& Buffer::getLevel() {
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
	
	bool Buffer::existAtLevel(const std::string &name) {
		std::vector<std::string> names = splitByDelimiter(name, '.');
		return getLevel().find(names[0]) != getLevel().end();
	}
	
	bool Buffer::exist(const YAML::Node &node) {
		std::string name;
		if(node.IsScalar()) {
			node >> name;
		} else {
			node["var"] >> name;
		}
		for(auto& level: objectsLevels) {
			if(level.find(name) != level.end())
				return true;
		}
		return false;
	}
}
