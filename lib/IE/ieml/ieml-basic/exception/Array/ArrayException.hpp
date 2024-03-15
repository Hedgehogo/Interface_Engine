#pragma once

#include <IEML/node/exception/Node/NodeException.hpp>

namespace ie {
	template<size_t size_>
	class ArrayException : public ieml::NodeException{
	public:
		ArrayException(ieml::Mark mark);
		
		auto get_description() const -> ieml::String override;
		
		auto clone() const -> ArrayException* override;;
	};
}

#include "ArrayException.inl"