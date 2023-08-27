#pragma once

#include <variant>
#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/IComponent/InitInfo/InitInfo.hpp"

namespace ie {
	template<typename T = std::monostate>
	struct BasicActionInitInfo {
		using AdditionalType = T;
		
		sf::RenderWindow& window;
		sf::RenderTarget& renderTarget;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		T additional;
		
		BasicActionInitInfo(
			sf::RenderWindow& window_,
			sf::RenderTarget& renderTarget_,
			InteractionManager& interactionManager_,
			InteractionStack& interactionStack_,
			IPanelManager& panelManager_,
			T additional_
		);
		
		BasicActionInitInfo(BasicActionInitInfo<> initInfo, T additional_);
		
		BasicActionInitInfo(InitInfo initInfo, T additional_);
		
		BasicActionInitInfo<T> copy(sf::RenderWindow& window_) const;
		
		BasicActionInitInfo<T> copy(sf::RenderTarget& renderTarget_) const;
		
		BasicActionInitInfo<T> copy(InteractionManager& interactionManager_) const;
		
		BasicActionInitInfo<T> copy(InteractionStack& interactionStack_) const;
		
		BasicActionInitInfo<T> copy(IPanelManager& panelManager_) const;
		
		BasicActionInitInfo<T> copy(T additional_) const;
		
		BasicActionInitInfo<> toGeneral() const;
	};
	
	using ActionInitInfo = BasicActionInitInfo<>;
}

#include "BasicActionInitInfo.inl"
