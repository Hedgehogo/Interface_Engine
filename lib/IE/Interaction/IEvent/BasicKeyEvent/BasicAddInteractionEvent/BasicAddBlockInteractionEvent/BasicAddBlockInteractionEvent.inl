namespace ui {
	template<typename T>
	void BasicAddBlockInteractionEvent<T>::stopPressed() {
	}
	
	template<typename T>
	BasicAddBlockInteractionEvent<T>::BasicAddBlockInteractionEvent(IBaseInteraction& interaction) : BasicAddInteractionEvent<T>(interaction) {
	}
	
	template<typename T>
	BasicAddBlockInteractionEvent<T>* BasicAddBlockInteractionEvent<T>::copy() {
		return new BasicAddBlockInteractionEvent<T>{*this};
	}
}
