//included into BasicAddSValueAction.hpp

namespace ie {
	namespace make_system {
		template<typename A_, typename Value_, typename _>
		BasicAddSValueAction<A_, Value_, _>::BasicAddSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant) :
			value(std::move(value)), constant(std::forward<typename Value_::T>(constant)) {
		}
		
		template<typename A_, typename Value_, typename _>
		auto BasicAddSValueAction<A_, Value_, _>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicAddSValueAction<A_, Value_>* {
			return new ie::BasicAddSValueAction<A_, Value_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_, typename Value_, typename _>
	BasicAddSValueAction<A_, Value_, _>::BasicAddSValueAction(Make&& make, BasicActionInitInfo<A_> init_info) :
		value(make.value.make(SInitInfo{init_info})), constant(std::forward<typename Value_::T>(make.constant)) {
	}
	
	template<typename A_, typename Value_, typename _>
	auto BasicAddSValueAction<A_, Value_, _>::update(bool active) -> void {
		if(active) {
			value.set(value.get() + constant);
		}
	}
}

template<typename A_, typename Value_>
auto ieml::Decode<char, ie::make_system::BasicAddSValueAction<A_, Value_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicAddSValueAction<A_, Value_> > {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicAddSValueAction<A_, Value_>{
		map.at("value").except().as<ie::MakeDyn<Value_> >().except(),
		map.at("constant").except().as<typename Value_::T>().except(),
	};
}
