#pragma once

#include "../ISizing2.hpp"
#include <functional>

namespace ie {
	class FnSizing2 : public virtual ISizing2 {
	public:
		using FindSizeFn = std::function<sf::Vector2f(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize)>;
		using GetParentSizeFn = std::function<sf::Vector2f(sf::Vector2f objectMinSize)>;
		
		struct Make : public virtual ISizing2::Make {
			FindSizeFn findSizeFn;
			GetParentSizeFn getParentSizeFn;
			
			Make() = default;
			
			Make(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn);
			
			FnSizing2* make(Sizing2InitInfo initInfo) override;
		};
		
		FnSizing2(Make&& make, Sizing2InitInfo initInfo);
		
		FnSizing2(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn);
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		FnSizing2* copy() override;
	
	protected:
		FindSizeFn findSizeFn;
		GetParentSizeFn getParentSizeFn;
		sf::RenderTarget* renderTarget;
		sf::Vector2f normalSize;
	};
}
