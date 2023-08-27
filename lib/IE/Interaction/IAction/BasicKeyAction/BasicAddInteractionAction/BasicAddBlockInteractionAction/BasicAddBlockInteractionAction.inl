namespace ie {
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
