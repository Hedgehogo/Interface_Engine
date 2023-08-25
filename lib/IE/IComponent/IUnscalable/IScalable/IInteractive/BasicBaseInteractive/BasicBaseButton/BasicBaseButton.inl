namespace ui {
	template<typename T>
	BasicBaseButton<T>::BasicBaseButton(BoxPtr<IScalable::Make>&& background, BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional) :
		BasicBaseInteractive<T>(std::move(interaction), initInfo, additional), background(background->make(initInfo)) {
	}
	
	template<typename T>
	BasicBaseButton<T>::BasicBaseButton(BoxPtr<IScalable>&& background, BoxPtr<IBasicInteraction<T> >&& interaction) :
		BasicBaseInteractive<T>(std::move(interaction)), background(std::move(background)) {
	}
	
	template<typename T>
	void BasicBaseButton<T>::init(InitInfo initInfo, T additional) {
		BasicBaseInteractive<T>::init(initInfo, additional);
		background->init(initInfo);
	}
	
	template<typename T>
	void BasicBaseButton<T>::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
	}
	
	template<typename T>
	sf::Vector2f BasicBaseButton<T>::getAreaPosition() const {
		return background->getAreaPosition();
	}
	
	template<typename T>
	sf::Vector2f BasicBaseButton<T>::getAreaSize() const {
		return background->getAreaSize();
	}
	
	template<typename T>
	sf::Vector2f BasicBaseButton<T>::getMinSize() const {
		return background->getMinSize();
	}
	
	template<typename T>
	sf::Vector2f BasicBaseButton<T>::getNormalSize() const {
		return background->getNormalSize();
	}
	
	template<typename T>
	const IScalable& BasicBaseButton<T>::getBackground() const {
		return *background;
	}
	
	template<typename T>
	bool BasicBaseButton<T>::updateInteractions(sf::Vector2f mousePosition) {
		bool backgroundUpdate = background->updateInteractions(mousePosition);
		return BasicBaseInteractive<T>::updateInteractions(mousePosition) || backgroundUpdate;
	}
	
	template<typename T>
	void BasicBaseButton<T>::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}