namespace ie {
	namespace make_system {
		template<typename A_>
		auto BasicEmptyAction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicEmptyAction<A_>* {
			return new ie::BasicEmptyAction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicEmptyAction<A_>::BasicEmptyAction(Make&&, BasicActionInitInfo<A_>) {
	}
	
	template<typename A_>
	auto BasicEmptyAction<A_>::update(bool) -> void {
	}
}
