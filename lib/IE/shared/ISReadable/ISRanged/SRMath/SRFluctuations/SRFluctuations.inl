#include <cmath>

namespace ie {
	namespace detail {
		template<typename T_>
		auto Fluctuations<T_>::sin(T_ const& value) -> T_ {
			return static_cast<T_>(std::sin(static_cast<double>(value)));
		}
		
		template<typename T_>
		auto Fluctuations<T_>::cos(T_ const& value) -> T_ {
			return static_cast<T_>(std::cos(static_cast<double>(value)));
		}
	}
	
	namespace make_system {
		template<typename T_, T_(* Fn_)(T_ const&)>
		SRFluctuations<T_, Fn_>::SRFluctuations(MakeDyn<ie::ISRanged<T_> > value, T_ amplitude, T_ frequency, T_ phase) :
			value(std::move(value)), amplitude(amplitude), frequency(frequency), phase(phase) {
		}
		
		template<typename T_, T_(* Fn_)(T_ const&)>
		auto SRFluctuations<T_, Fn_>::make(SInitInfo init_info) -> rttb::Dyn {
			return rttb::Dyn{new ie::SRFluctuations<T_, Fn_>{std::move(*this), SInitInfo{init_info}}};
		}
	}
	
	template<typename T_, T_(* Fn_)(T_ const&)>
	SRFluctuations<T_, Fn_>::SRFluctuations(Make&& make, ie::SInitInfo init_info) :
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
		amplitude_(make.amplitude),
		frequency_(make.frequency),
		phase_(make.phase){
		this->upper_bound_ = amplitude_;
		this->lower_bound_ = -amplitude_;
	}
	
	template<typename T_, T_(* Fn_)(T_ const&)>
	auto SRFluctuations<T_, Fn_>::get() const -> T_ {
		auto value{amplitude_ * static_cast<T_>(Fn_(frequency_ * value_.get().get() + phase_))};
		return std::min(std::max(value, this->lower_bound_), this->upper_bound_);
	}
}

template<typename T_, T_(* Fn_)(T_ const&)>
orl::Option<ie::make_system::SRFluctuations<T_, Fn_> > ieml::Decode<char, ie::make_system::SRFluctuations<T_, Fn_> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::make_system::SRFluctuations<T_, Fn_>{
		map.at("value").except().as<ie::MakeDyn<ie::ISRanged<T_> > >().except(),
		map.get_as<T_>("amplitude").except().ok_or(1),
		map.get_as<T_>("frequency").except().ok_or(1),
		map.get_as<T_>("phase").except().ok_or(0)
	};
	
}
