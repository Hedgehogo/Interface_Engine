#pragma once

#include "../IMovePanelInteraction.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

namespace ie {
	class DontMovePanelInteraction : public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			DontMovePanelInteraction* make(PanelActionInitInfo initInfo) override;
		};
		
		DontMovePanelInteraction(Make&& make, PanelActionInitInfo initInfo);
		
		DontMovePanelInteraction() = default;
		
		bool getAtStart() override;
		
		void move(sf::Vector2i) override;
		
		void start(sf::Vector2i) override;
		
		void update(sf::Vector2i) override;
		
		void init(PanelActionInitInfo) override;
		
		void setPanel(Panel&) override;
		
		DontMovePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontMovePanelInteraction> {
		static bool decodePointer(const YAML::Node&, DontMovePanelInteraction*& dontMovePanelInteraction);
	};
}