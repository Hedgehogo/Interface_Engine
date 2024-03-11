namespace ie {
	namespace make_system {
		template<typename T>
		BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
			BasicAddInteractionAction<T>(std::move(interaction)) {
		}
		
		template<typename T>
		auto BasicAddBlockInteractionAction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicAddBlockInteractionAction<T>* {
			return new ie::BasicAddBlockInteractionAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicAddInteractionAction<T>(std::move(make), init_info) {
	}
	
	template<typename T>
	auto BasicAddBlockInteractionAction<T>::stop_pressed() -> void {
	}
	
	template<typename T>
	auto BasicAddBlockInteractionAction<T>::finish() -> void {
	}
}
