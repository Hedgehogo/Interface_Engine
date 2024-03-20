#include <cmath>

namespace ie {
	namespace make_system {
		template<typename T_>
		SRLerp<T_>::SRLerp(MakeDyn<ie::ISRanged<T_> > value, T_ k, T_ b) :
			value(std::move(value)), k(k), b(b) {
		}
		
		template<typename T_>
		SRLerp<T_>::SRLerp(MakeDyn<ie::ISRanged<T_> > value, sf::Vector2<T_> a, sf::Vector2<T_> b) :
			value(std::move(value)), k((b.y - a.y) / (b.x - a.x)), b(a.y - (k * a.x)) {
		}
		
		template<typename T_>
		auto SRLerp<T_>::make(SInitInfo init_info) -> rttb::Dyn {
			return rttb::Dyn{new ie::SRLerp<T_>{std::move(*this), SInitInfo{init_info}}};
		}
	}
	
	template<typename T_>
	SRLerp<T_>::SRLerp(Make&& make, ie::SInitInfo init_info) :
		SRanged<T_>(
			make.data,
			init_info
		),
		value_(
			DynBuffer::get(
				std::move(make.value),
				init_info
			),
			[this](auto const&){
				this->reset();
			}
		),
		k_(make.k),
		b_(make.b){
		if(k_ >= 0) {
			this->upper_bound_ = k_ * value_.get().get_upper_bound() + b_;
			this->lower_bound_ = k_ * value_.get().get_lower_bound() + b_;
		} else {
			this->upper_bound_ = k_ * value_.get().get_lower_bound() + b_;
			this->lower_bound_ = k_ * value_.get().get_upper_bound() + b_;
		}
	}
	
	template<typename T_>
	auto SRLerp<T_>::get() const -> T_ {
		return k_*value_.get().get() + b_;
	}
	
	template<typename T_>
	auto SRLerp<T_>::set_upper_bound(T_ upper_bound) -> void {
		SRanged<T_>::set_upper_bound(upper_bound);
		if(k_ >= 0){
			value_.get().set_upper_bound((this->upper_bound_ - b_) / k_);
		} else {
			value_.get().set_lower_bound((this->upper_bound_ - b_) / k_);
		}
	}
	
	template<typename T_>
	auto SRLerp<T_>::set_lower_bound(T_ lower_bound) -> void {
		SRanged<T_>::set_lower_bound(lower_bound);
		if(k_ >= 0) {
			value_.get().set_lower_bound((this->lower_bound_ - b_) / k_);
		} else {
			value_.get().set_upper_bound((this->lower_bound_ - b_) / k_);
		}
	}
	
	template<typename T_>
	auto SRLerp<T_>::set_bounds(T_ lower_bound, T_ upper_bound) -> void {
		SRanged<T_>::set_bounds(lower_bound, upper_bound);
		if(k_ >= 0) {
			value_.get().set_bounds((this->lower_bound_ - b_) / k_, (this->upper_bound_ - b_) / k_);
		} else {
			value_.get().set_bounds((this->upper_bound_ - b_) / k_, (this->lower_bound_ - b_) / k_);
		}
	}
}

template<typename T_>
orl::Option<ie::make_system::SRLerp<T_> > ieml::Decode<char, ie::make_system::SRLerp<T_> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	for(auto& k_node : map.at("k").ok_or_none()) {
		auto k{k_node.as<T_>().except()};
		if(k == 0){
			throw ie::SRLerpException{k_node.get_mark(), false};
		}
		return ie::make_system::SRLerp<T_>{
			map.at("value").except().as<ie::MakeDyn<ie::ISRanged<T_> > >().except(),
			k,
			map.get_as<T_>("b").except().ok_or({})
		};
	}
	const auto a = map.at("a").except().as<sf::Vector2<T_> >().except();
	const auto b_node = map.at("b").except();
	const auto b = b_node.as<sf::Vector2<T_> >().except();
	if(a.x == b.x){
		throw ie::SRLerpException{b_node.get_mark(), true};
	}
	return ie::make_system::SRLerp<T_>{
		map.at("value").except().as<ie::MakeDyn<ie::ISRanged<T_> > >().except(),
		a,
		b
	};
	
}
