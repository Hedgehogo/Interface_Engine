namespace ie {
	namespace make_system {
		template<typename T>
		BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
			BasicAddInteractionAction<T>(std::move(interaction)) {
		}
		
		template<typename T>
		ie::BasicAddBlockInteractionAction<T>* BasicAddBlockInteractionAction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicAddBlockInteractionAction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(Make&& make, BasicActionInitInfo<T> initInfo) :
		BasicAddInteractionAction<T>(std::move(make), initInfo) {
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
		BasicAddInteractionAction<T>(std::move(interaction)) {
	}
	
	template<typename T>
	void BasicAddBlockInteractionAction<T>::stopPressed() {
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>* BasicAddBlockInteractionAction<T>::copy() {
		return new BasicAddBlockInteractionAction<T>{*this};
	}
}
