namespace ui {
	namespace detail {
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, uint state) :
			interaction(std::move(interaction)), state(state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(uint state) :
			interaction(nullptr), state(state) {
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state) :
		hotkeyStates(std::move(hotkeys)), nowHotkeys(nullptr) {
		if(this->hotkeyStates.size() <= state) {
			this->hotkeyStates.resize(state, {});
		}
		nowHotkeys = &this->hotkeyStates[state];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::init(BasicInteractionInitInfo<T> initInfo) {
		for(const auto& hotkeyState: hotkeyStates) {
			for(auto& hotkey: hotkeyState) {
				hotkey->interaction->init(initInfo);
			}
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::string) {
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::setHotkeyEvent(uint state, typename BasicHotkeyInteraction<T>::Hotkey* hotkeyEvent) {
		if(hotkeyStates.size() <= state) {
			hotkeyStates.resize(state, {});
		}
		hotkeyStates[state].emplace_back(hotkeyEvent);
	}
	
	template<typename T>
	std::vector<BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> > BasicHotkeyInteraction<T>::getHotkeys(int state) {
		return hotkeyStates[state];
	}
	
	template<typename T>
	BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> BasicHotkeyInteraction<T>::getHotkey(int state, int i) {
		return hotkeyStates[state][i];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::start(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->start(mousePosition);
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::update(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->update(mousePosition);
			if(hotkey->interaction->isPress() && hotkey->state != std::numeric_limits<uint>::max()) {
				finish(mousePosition);
				nowHotkeys = &hotkeyStates[hotkey->state];
				start(mousePosition);
			}
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::finish(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->finish(mousePosition);
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::copy() {
		return new BasicHotkeyInteraction<T>{*this};
	}
	
	template<typename T>
	bool Decode<detail::BasicHotkeyInteractionHotkey<T>*>::decode(const YAML::Node& node, detail::BasicHotkeyInteractionHotkey<T>*& hotkey) {
		hotkey = new detail::BasicHotkeyInteractionHotkey<T>{
			convDef(node["interaction"], BoxPtr<BasicKeysInteraction<T> >{}),
			convDef(node["state"], std::numeric_limits<uint>::max())
		};
		return true;
	}
}