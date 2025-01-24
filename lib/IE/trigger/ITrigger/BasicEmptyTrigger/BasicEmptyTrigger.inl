namespace ie {
	namespace make_system {
		template<typename A_>
		auto BasicEmptyTrigger<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicEmptyTrigger<A_>* {
			return new ie::BasicEmptyTrigger<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicEmptyTrigger<A_>::BasicEmptyTrigger(Make&&, BasicActionInitInfo<A_>) {
	}
	
	template<typename A_>
	BasicEmptyTrigger<A_>::BasicEmptyTrigger() {
	}
	
	template<typename A_>
	auto BasicEmptyTrigger<A_>::start() -> void {
	}
	
	template<typename A_>
	auto BasicEmptyTrigger<A_>::handle_event(Event event) -> bool {
		return false;
	}
	
	template<typename A_>
	auto BasicEmptyTrigger<A_>::update() -> void {
	}
	
	template<typename A_>
	auto BasicEmptyTrigger<A_>::finish() -> void {
	}
}

template<typename A_>
auto ieml::Decode<char, ie::BasicEmptyTrigger<A_> >::decode(ieml::Node const&) -> orl::Option<ie::BasicEmptyTrigger<A_> > {
	return ie::BasicEmptyTrigger<A_>{};
}
