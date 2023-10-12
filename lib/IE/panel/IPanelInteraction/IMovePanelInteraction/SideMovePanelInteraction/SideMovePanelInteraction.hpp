#pragma once

#include "../IMovePanelInteraction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class SideMovePanelInteraction : public BasePanelInteraction, public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			float coefficient;
			float offset;
			bool horizontal;
			bool atStart = false;
			
			Make(float coefficient, float offset, bool horizontal, bool atStart = false);
			
			SideMovePanelInteraction* make(PanelActionInitInfo initInfo) override;
		};
		
		SideMovePanelInteraction(Make&& make, PanelActionInitInfo initInfo);
		
		SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool atStart = false);
		
		bool getAtStart() override;
		
		void move(sf::Vector2i mousePosition) override;
		
		SideMovePanelInteraction* copy() override;
	
	protected:
		float coefficient;
		float offset;
		bool horizontal;
		bool atStart;
	};
	
	template<>
	struct DecodePointer<SideMovePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, SideMovePanelInteraction*& sideMovePanelInteraction);
	};
}
