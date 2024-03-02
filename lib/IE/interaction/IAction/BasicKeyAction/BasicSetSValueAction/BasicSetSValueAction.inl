//included into BasicSetSValueAction.hpp

namespace ie {
	namespace make_system {
		template<typename T_, typename Value_, typename _>
		BasicSetSValueAction<T_, Value_, _>::BasicSetSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant) :
			value(std::move(value)), constant(std::forward<typename Value_::T>(constant)) {
		}
		
		template<typename T_, typename Value_, typename _>
		auto BasicSetSValueAction<T_, Value_, _>::make(BasicActionInitInfo<T_> init_info) -> ie::BasicSetSValueAction<T_, Value_>* {
			return new ie::BasicSetSValueAction<T_, Value_>{std::move(*this), init_info};
		}
	}
}

template<typename T_, typename Value_>
auto ieml::Decode<char, ie::make_system::BasicSetSValueAction<T_, Value_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicSetSValueAction<T_, Value_> > {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicSetSValueAction<T_, Value_>{
		map.at("value").except().as<ie::MakeDyn<Value_> >().except(),
		map.at("constant").except().as<typename Value_::T>().except(),
	};
}

namespace ie {
	template<typename T_, typename Value_, typename _>
	BasicSetSValueAction<T_, Value_, _>::BasicSetSValueAction(Make&& make, BasicActionInitInfo<T_> init_info) :
		value(make.value.make(SInitInfo{init_info})), constant(std::forward<typename Value_::T>(make.constant)) {
	}
	
	template<typename T_, typename Value_, typename _>
	auto BasicSetSValueAction<T_, Value_, _>::start_pressed() -> void {
	}
	
	template<typename T_, typename Value_, typename _>
	auto BasicSetSValueAction<T_, Value_, _>::stop_pressed() -> void {
		value.set(constant);
	}
	
	template<typename T_, typename Value_, typename _>
	auto BasicSetSValueAction<T_, Value_, _>::while_pressed() -> void {
	}
	
	template<typename T_, typename Value_, typename _>
	auto BasicSetSValueAction<T_, Value_, _>::while_not_pressed() -> void {
	}
}
