#include "buffer.hpp"
#include "modules/appendix/yaml-cpp/shared/vector/iSVector2.hpp"
#include "modules/appendix/yaml-cpp/shared/list/iSList.hpp"

namespace ui {
	std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter) {
		std::stringstream strStream{str};
		std::vector<std::string> result;
		std::string substr;
		while(std::getline(strStream, substr, delimiter)) {
			result.push_back(substr);
		}
		return result;
	}
	
	PIShared getVectorAxis(const PIShared& vector, const std::string& name) {
		std::shared_ptr<ISVector2> vec{std::dynamic_pointer_cast<ISVector2>(vector)};
		if(vec == nullptr) {
			throw BufferVariableNotFoundException{name, type_name<IShared>()};
		}
		if(name == "x") {
			return vec->getXPtr();
		} else if(name == "y") {
			return vec->getYPtr();
		}
		throw BufferVariableNotFoundException{name, type_name<IShared>()};
	}
	
	PIShared getListElement(const PIShared& var, const std::string& name) {
		std::shared_ptr<ISList> list{std::dynamic_pointer_cast<ISList>(var)};
		if(list == nullptr) {
			throw BufferVariableNotFoundException{name, type_name<IShared>()};
		}
		return list->getElementPtr(std::stoull(name));
	}
	
	std::vector<std::map<std::string, PIShared>> Buffer::objectsLevels = {1, std::map<std::string, PIShared>{}};
	std::vector<std::pair<std::regex, Buffer::GetOption>> Buffer::options = {
		std::make_pair(std::regex{R"([xy])"}, getVectorAxis),
		std::make_pair(std::regex{R"(\d+)"}, getListElement)
	};
	
	PIShared Buffer::getVariable(const PIShared& var, std::vector<std::string>& names) {
		if(!names.empty()) {
			std::string name = names[names.size() - 1];
			names.pop_back();
			auto optionFunction = std::find_if(options.begin(), options.end(), [&](const std::pair<std::regex, GetOption>& option) {
				return std::regex_match(name.cbegin(), name.cend(), option.first);
			});
			if(optionFunction != options.end()) {
				return optionFunction->second(getVariable(var, names), name);
			} else {
				throw BufferVariableNotFoundException{name, type_name<IShared>()};
			}
		}
		return var;
	}
	
	std::map<std::string, PIShared>& Buffer::getLevel() {
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
	
	bool Buffer::existAtLevel(const std::string& name) {
		std::vector<std::string> names = splitByDelimiter(name, '.');
		return getLevel().find(names[0]) != getLevel().end();
	}
	
	bool Buffer::exist(const YAML::Node& node) {
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
