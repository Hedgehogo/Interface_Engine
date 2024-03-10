#pragma once
#include <IEML/node/exception/Node/NodeException.hpp>

namespace ie {
	class SRLerpException : public ieml::NodeException{
	public:
		SRLerpException(ieml::Mark mark, bool constructor_with_point);
		
		auto get_description() const -> ieml::String override;
		
		SRLerpException* clone() const override;
	
	protected:
		bool constructor_with_point;
	};
}