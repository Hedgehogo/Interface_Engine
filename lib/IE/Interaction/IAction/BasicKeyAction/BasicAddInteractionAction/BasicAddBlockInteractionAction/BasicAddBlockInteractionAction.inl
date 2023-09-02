namespace ie {
	template<typename T>
	BasicAddBlockInteractionAction<T>::Make::Make(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction) :
		BasicAddInteractionAction<T>::Make(std::move(interaction)) {
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>* BasicAddBlockInteractionAction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicAddBlockInteractionAction<T>{std::move(*this), initInfo};
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
