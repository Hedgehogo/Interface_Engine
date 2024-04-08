#include <cmath>

namespace ie {
	namespace make_system {
		template<typename T_>
		SRBezierCurve<T_>::SRBezierCurve(
			MakeDyn<ie::ISRanged<T_> > value,
			std::array<T_, 4> points
		) :
			ie::SRanged<T_>::Make(),
			value(std::move(value)),
			points(points){
		}
		
		template<typename T_>
		auto SRBezierCurve<T_>::make(SInitInfo init_info) -> rttb::Dyn {
			return rttb::Dyn{new ie::SRBezierCurve<T_>{std::move(*this), SInitInfo{init_info}}};
		}
	}
	
	template<typename T_>
	SRBezierCurve<T_>::SRBezierCurve(SRBezierCurve::Make&& make, ie::SInitInfo init_info) :
		SRanged<T_>(
			std::forward<T_>(make.data),
			init_info
		),
		value_(DynBuffer::get(std::move(make.value), init_info), [this](auto const&){
			this->reset();
		}),
		points_(make.points),
		size_(1){
		value_.get().set_bounds(0, 1);
	}
	
	template<typename T_>
	auto SRBezierCurve<T_>::get() const -> T_ {
		auto t{value_.get().get()};
		return this->lower_bound_ + (size_ * (
			std::pow(1 - t, 3) * points_[0] +
			3 * t * std::pow(1 - t, 2) * points_[1] +
			3 * std::pow(t, 2) * (1 - t) * points_[2] +
			std::pow(t, 3) * points_[3]
		)); // y component of the parametric equation of the Bézier curve
	}
	
	template<typename T_>
	auto SRBezierCurve<T_>::set_upper_bound(T_ upper_bound) -> void {
		SRanged<T_>::set_upper_bound(upper_bound);
		size_ = this->upper_bound_ - this->lower_bound_;
	}
	
	template<typename T_>
	auto SRBezierCurve<T_>::set_lower_bound(T_ lower_bound) -> void {
		SRanged<T_>::set_lower_bound(lower_bound);
		size_ = this->upper_bound_ - this->lower_bound_;
	}
	
	template<typename T_>
	auto SRBezierCurve<T_>::set_bounds(T_ lower_bound, T_ upper_bound) -> void {
		SRanged<T_>::set_bounds(lower_bound, upper_bound);
		size_ = this->upper_bound_ - this->lower_bound_;
	}
}

template<typename T_>
orl::Option<ie::make_system::SRBezierCurve<T_> > ieml::Decode<char, ie::make_system::SRBezierCurve<T_> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	auto points_node{map.at("points").except()};
	auto points{points_node.as<std::array<T_, 4> >().except()};
	auto upper{std::max(points[0], points[3])};
	auto lower{std::min(points[0], points[3])};
	
	auto if_corrected_bound{
		[&points, &points_node](size_t i) {
			if(1 < points[i] || points[i] < 0) {
				throw ie::BezierCurveException<T_>{points_node.get_mark(), i, points[i]};
			}
		}
	};
	auto if_corrected_value{
		[&points, &points_node, &upper, &lower](size_t i) {
			if(upper < points[i] || points[i] < lower) {
				throw ie::BezierCurveException<T_>{points_node.get_mark(), i, {points[0], points[i], points[3]}};
			}
		}
	};
	if_corrected_bound(0);
	if_corrected_bound(3);
	if_corrected_value(1);
	if_corrected_value(2);
	return ie::make_system::SRBezierCurve<T_> {
		map.at("value").except().as<ie::MakeDyn<ie::ISRanged<T_> > >().except(),
		points
	};
}
