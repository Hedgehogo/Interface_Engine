#pragma once

#include <variant>
#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/IComponent/InitInfo/InitInfo.hpp"

namespace ui {
	template<typename T = std::monostate>
	struct BasicInteractionInitInfo {
		using AdditionalType = T;
		
		sf::RenderWindow& window;
		sf::RenderTarget& renderTarget;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		T additional;
		
		BasicInteractionInitInfo(
			sf::RenderWindow& window_,
			sf::RenderTarget& renderTarget_,
			InteractionManager& interactionManager_,
			InteractionStack& interactionStack_,
			IPanelManager& panelManager_,
			T additional_
		);
		
		BasicInteractionInitInfo(BasicInteractionInitInfo<> initInfo, T additional_);
		
		BasicInteractionInitInfo(InitInfo initInfo, T additional_);
		
		BasicInteractionInitInfo<T> copy(sf::RenderWindow& window_) const;
		
		BasicInteractionInitInfo<T> copy(sf::RenderTarget& renderTarget_) const;
		
		BasicInteractionInitInfo<T> copy(InteractionManager& interactionManager_) const;
		
		BasicInteractionInitInfo<T> copy(InteractionStack& interactionStack_) const;
		
		BasicInteractionInitInfo<T> copy(IPanelManager& panelManager_) const;
		
		BasicInteractionInitInfo<T> copy(T additional_) const;
		
		BasicInteractionInitInfo<> toGeneral() const;
	};
	
	using InteractionInitInfo = BasicInteractionInitInfo<>;
}

#include "BasicInteractionInitInfo.inl"
