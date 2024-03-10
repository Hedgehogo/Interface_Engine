#include <cmath>

namespace ie {
	namespace make_system {
		template<typename T_>
		SRLerp<T_>::SRLerp(MakeDyn<ie::ISRanged<T_> > x, T_ k, T_ b) :
			x(std::move(x)), k(k), b(b) {
		}
		
		template<typename T_>
		SRLerp<T_>::SRLerp(MakeDyn<ie::ISRanged<T_> > x, sf::Vector2<T_> a, sf::Vector2<T_> b) :
			x(std::move(x)), k((b.y - a.y) / (b.x - a.x)), b(a.y - (k * a.x)) {
		}
		
		template<typename T_>
		auto SRLerp<T_>::make(SInitInfo init_info) -> rttb::Dyn {
			return rttb::Dyn{new ie::SRLerp<T_>{std::move(*this), SInitInfo{init_info}}};
		}
	}
	
	template<typename T_>
	SRLerp<T_>::SRLerp(Make&& make, ie::SInitInfo init_info) :
		SRanged<T_>(
			{},
			init_info
		),
		value_(
			DynBuffer::get(
				std::move(make.x),
				init_info
			),
			[this](auto const&){
				this->reset();
			}
		),
		k_(make.k),
		b_(make.b){
		this->upper_bound_ = value_.get().get_upper_bound();
		this->lower_bound_ = value_.get().get_lower_bound();
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
}

template<typename T_>
orl::Option<ie::make_system::SRLerp<T_> > ieml::Decode<char, ie::make_system::SRLerp<T_> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	for(auto& k : map.at("k").ok_or_none()) {
		return ie::make_system::SRLerp<T_>{
			map.at("value").except().as<ie::MakeDyn<ie::ISRanged<T_> > >().except(),
			k.as<T_>().except(),
			map.get_as<T_>("b").except().ok_or({})
		};
	}
	return ie::make_system::SRLerp<T_>{
		map.at("value").except().as<ie::MakeDyn<ie::ISRanged<T_> > >().except(),
		map.at("a").except().as<sf::Vector2<T_> >().except(),
		map.at("b").except().as<sf::Vector2<T_> >().except()
	};
	
}
