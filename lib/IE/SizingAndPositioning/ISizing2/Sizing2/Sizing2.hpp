#pragma once

#include "../ISizing2.hpp"
#include "../../ISizing/ISizing.hpp"

namespace ie {
	class Sizing2 : public ISizing2 {
	public:
		struct Make : public ISizing2::Make {
			BoxPtr<ISizing::Make> horizontal;
			BoxPtr<ISizing::Make> vertical;
			
			Make(BoxPtr<ISizing::Make>&& horizontal, BoxPtr<ISizing::Make>&& vertical);
			
			Make(bool relativeParent);
			
			Make(sf::Vector2f constSize);
			
			Make(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget = false);
			
			Make(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition);
			
			Sizing2* make(Sizing2InitInfo initInfo) override;
		};
		
		Sizing2(Make&& make, Sizing2InitInfo initInfo);
		
		Sizing2(BoxPtr<ISizing>&& horizontal, BoxPtr<ISizing>&& vertical);
		
		Sizing2(bool relativeParent);
		
		Sizing2(sf::Vector2f constSize);
		
		Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget = false);
		
		Sizing2(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition);
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		Sizing2* copy() override;
	
	protected:
		BoxPtr<ISizing> horizontal;
		BoxPtr<ISizing> vertical;
		sf::RenderTarget* renderTarget;
	};
	
	template<>
	struct DecodePointer<Sizing2> {
		static bool decodePointer(const YAML::Node& node, Sizing2*& sizing2);
	};
}
