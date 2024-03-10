#include "SRLerpException.hpp"

namespace ie {
	SRLerpException::SRLerpException(ieml::Mark mark, bool constructor_with_point) : ieml::NodeException(mark), constructor_with_point(constructor_with_point) {
	}
	
	auto SRLerpException::get_description() const -> ieml::String {
		return ieml::String("The line cannot be parallel to the Ox axis: ") +
			[this]() -> ieml::String {
				if(constructor_with_point) {
					return "values at coordinates x cannot be equal";
				}
				return "the value of `k` cannot equal 0";
			}();
	}
	
	SRLerpException* SRLerpException::clone() const {
		return new SRLerpException{*this};
	}
}