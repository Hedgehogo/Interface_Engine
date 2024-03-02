#pragma once

#include "../yaml.hpp"
#include "../../exception/BaseException.hpp"

namespace ie {
	class BaseYamlException : public BaseException {
	public:
		BaseYamlException(YAML::Mark mark);
		
		auto get_note() const -> std::string override;
		
		auto get_mark() const -> YAML::Mark;
	
	protected:
		YAML::Mark mark_;
	};
}
