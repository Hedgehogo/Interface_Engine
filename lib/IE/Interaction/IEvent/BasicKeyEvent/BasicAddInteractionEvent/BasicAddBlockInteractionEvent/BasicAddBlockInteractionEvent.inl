namespace ie {
	template<typename T>
	void BasicAddBlockInteractionEvent<T>::stopPressed() {
	}
	
	template<typename T>
	BasicAddBlockInteractionEvent<T>::BasicAddBlockInteractionEvent(IBasicInteraction<T>& interaction) :
		BasicAddInteractionEvent<T>(interaction) {
	}
	
	template<typename T>
	BasicAddBlockInteractionEvent<T>* BasicAddBlockInteractionEvent<T>::copy() {
		return new BasicAddBlockInteractionEvent<T>{*this};
	}
}
