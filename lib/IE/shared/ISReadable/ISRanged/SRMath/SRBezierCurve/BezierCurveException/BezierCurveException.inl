namespace ie {
	template<typename T_>
	BezierCurveException<T_>::BezierCurveException(
		ieml::Mark mark,
		size_t i,
		std::array<T_, 3> points
	) :
		NodeException(mark),
		str(
			ieml::String("point [") +
			std::to_string(i) +
			ieml::String{"] = `"} +
			std::to_string(points[1]) +
			ieml::String{"`"} +
			ieml::String(" is out of the range between [0] = `") +
			std::to_string(points[0]) +
			ieml::String{"` and "} +
			ieml::String("[3] = `") +
			std::to_string(points[2]) +
			ieml::String{"`"}
		){
	}
	
	template<typename T_>
	BezierCurveException<T_>::BezierCurveException(
		ieml::Mark mark,
		size_t i,
		T_ point
	) :
		NodeException(mark),
		str(
			ieml::String{"value ["} +
			std::to_string(i) +
			ieml::String{"] = `"} +
			std::to_string(point) +
			ieml::String{"` is out of the range between `"} +
			std::to_string(0) +
			ieml::String{"` and `"} +
			std::to_string(1) +
			ieml::String{"`"}
		){
	}
	
	template<typename T_>
	ieml::String BezierCurveException<T_>::get_description() const {
		return str;
	}
	
	template<typename T_>
	BezierCurveException<T_>* BezierCurveException<T_>::clone() const {
		return new BezierCurveException<T_>{*this};
	}
}