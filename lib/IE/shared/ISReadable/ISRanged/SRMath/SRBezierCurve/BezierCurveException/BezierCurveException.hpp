#pragma once

#include <IEML/node/exception/Node/NodeException.hpp>
#include <array>

namespace ie {
	template<typename T_>
	class BezierCurveException : public ieml::NodeException{
	public:
		BezierCurveException(ieml::Mark mark, std::array<T_, 3> points, bool first_point_not_corrected);
		
		auto get_description() const -> std::string override;
		
		BezierCurveException<T_>* clone() const override;
	
	protected:
		std::array<T_, 3> points_;
		bool first_point_not_corrected_;
	};
}

#include "BezierCurveException.inl"