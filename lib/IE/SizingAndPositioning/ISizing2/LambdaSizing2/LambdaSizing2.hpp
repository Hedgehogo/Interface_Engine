#pragma once

#include "../ISizing2.hpp"

namespace ie {
	class LambdaSizing2 : public virtual ISizing2 {
	public:
		struct Make : public virtual ISizing2::Make {
			sf::Vector2f (* findSize)(sf::Vector2f, sf::Vector2f, sf::Vector2f);
			sf::Vector2f (* getParentMinSize)(sf::Vector2f);
			
			Make(
				sf::Vector2f (* findSize)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize),
				sf::Vector2f (* getParentMinSize)(sf::Vector2f objectMinSize)
			);
			
			LambdaSizing2* make(Sizing2InitInfo initInfo) override;
		};
		
		LambdaSizing2(Make&& make, Sizing2InitInfo initInfo);
		
		explicit LambdaSizing2(
			sf::Vector2f (* findSize)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize),
			sf::Vector2f (* getParentMinSize)(sf::Vector2f objectMinSize)
		);
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		LambdaSizing2* copy() override;
	
	protected:
		sf::Vector2f (* sizing)(sf::Vector2f, sf::Vector2f, sf::Vector2f);
		sf::Vector2f (* minSize)(sf::Vector2f);
		sf::RenderTarget* renderTarget;
		sf::Vector2f normalSize;
	};
}
