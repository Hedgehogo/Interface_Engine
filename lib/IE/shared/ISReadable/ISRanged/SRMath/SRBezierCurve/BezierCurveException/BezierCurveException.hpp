#pragma once

#include <IEML/node/exception/Node/NodeException.hpp>
#include <array>

namespace ie {
	template<typename T_>
	class BezierCurveException : public ieml::NodeException{
	public:
		BezierCurveException(ieml::Mark mark, size_t i, std::array<T_, 3> points);
		
		BezierCurveException(ieml::Mark mark, size_t i, T_ point);
		
		auto get_description() const -> std::string override;
		
		BezierCurveException<T_>* clone() const override;
	
	protected:
		ieml::String str;
	};
}

#include "BezierCurveException.inl"