#include "Buffer.hpp"
#include "../shared/ISVector2/ISVector2.hpp"
#include "../shared/ISList/ISList.hpp"

namespace ie {
	std::vector<std::string> split_by_delimiter(const std::string& str, char delimiter) {
		std::stringstream str_stream{str};
		std::vector<std::string> result;
		std::string substr;
		while(std::getline(str_stream, substr, delimiter)) {
			result.push_back(substr);
		}
		return result;
	}
	
	PIShared get_vector_axis(const PIShared& vector, const std::string& name) {
		std::shared_ptr<ISVector2> vec{std::dynamic_pointer_cast<ISVector2>(vector)};
		if(vec == nullptr) {
			throw BufferVariableNotFoundException{name, type_name<IShared>()};
		}
		if(name == "x") {
			return vec->get_x_ptr();
		} else if(name == "y") {
			return vec->get_y_ptr();
		}
		throw BufferVariableNotFoundException{name, type_name<IShared>()};
	}
	
	PIShared get_list_element(const PIShared& var, const std::string& name) {
		std::shared_ptr<ISList> list{std::dynamic_pointer_cast<ISList>(var)};
		if(list == nullptr) {
			throw BufferVariableNotFoundException{name, type_name<IShared>()};
		}
		return list->get_element_ptr(std::stoull(name));
	}
	
	std::vector<std::map<std::string, PIShared>> Buffer::objects_levels_ = {1, std::map<std::string, PIShared>{}};
	std::vector<std::pair<std::regex, Buffer::GetOption>> Buffer::options_ = {
		std::make_pair(std::regex{R"([xy])"}, get_vector_axis),
		std::make_pair(std::regex{R"(\d+)"}, get_list_element)
	};
	
	PIShared Buffer::get_variable(const PIShared& var, std::vector<std::string>& names) {
		if(!names.empty()) {
			std::string name = names[names.size() - 1];
			names.pop_back();
			auto option_function = std::find_if(options_.begin(), options_.end(), [&](const std::pair<std::regex, GetOption>& option) {
				return std::regex_match(name.cbegin(), name.cend(), option.first);
			});
			if(option_function != options_.end()) {
				return option_function->second(get_variable(var, names), name);
			} else {
				throw BufferVariableNotFoundException{name, type_name<IShared>()};
			}
		}
		return var;
	}
	
	std::map<std::string, PIShared>& Buffer::get_level() {
		return objects_levels_[objects_levels_.size() - 1];
	}
	
	void Buffer::raise_nesting_level() {
		objects_levels_.emplace_back();
	}
	
	void Buffer::lower_nesting_level() {
		objects_levels_.pop_back();
	}
	
	void Buffer::read_level(std::function<void()> function) {
		objects_levels_.emplace_back();
		function();
		objects_levels_.pop_back();
	}
	
	bool Buffer::exist_at_level(const std::string& name) {
		std::vector<std::string> names = split_by_delimiter(name, '.');
		return get_level().find(names[0]) != get_level().end();
	}
	
	bool Buffer::exist(const YAML::Node& node) {
		std::string name;
		if(node.IsScalar()) {
			node >> name;
		} else {
			node["var"] >> name;
		}
		for(auto& level: objects_levels_) {
			if(level.find(name) != level.end())
				return true;
		}
		return false;
	}
}