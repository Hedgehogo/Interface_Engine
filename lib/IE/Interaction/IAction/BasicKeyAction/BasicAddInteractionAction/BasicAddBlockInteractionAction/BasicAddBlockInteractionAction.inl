namespace ie {
	template<typename T>
	void BasicAddBlockInteractionAction<T>::stopPressed() {
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(IBasicInteraction<T>& interaction) :
		BasicAddInteractionAction<T>(interaction) {
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>* BasicAddBlockInteractionAction<T>::copy() {
		return new BasicAddBlockInteractionAction<T>{*this};
	}
}
