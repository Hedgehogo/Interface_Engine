namespace ie {
	template<typename T_>
	BezierCurveException<T_>::BezierCurveException(
		ieml::Mark mark,
		std::array<T_, 3> points,
		bool first_point_not_corrected
	) :
		NodeException(mark),
		points_(points),
		first_point_not_corrected_(first_point_not_corrected){
	}
	
	template<typename T_>
	std::string BezierCurveException<T_>::get_description() const {
		return std::string("point ") +
			[this]{
				if(first_point_not_corrected_){
					return std::string{"[1] = `"} + std::to_string(points_[1]) + std::string{"`"};
				} else {
					return std::string{"[2] = `"} + std::to_string(points_[1]) + std::string{"`"};
				}
			}() +
			std::string(" is out of the range between [0] = `") +
			std::to_string(points_[0]) +
			std::string{"` and "} +
			std::string("[3] = `") +
			std::to_string(points_[2]) +
			std::string{"`"};
	}
	
	template<typename T_>
	BezierCurveException<T_>* BezierCurveException<T_>::clone() const {
		return new BezierCurveException<T_>{*this};
	}
}