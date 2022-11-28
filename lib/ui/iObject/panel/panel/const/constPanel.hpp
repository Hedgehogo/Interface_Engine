#pragma once
#include "../basePanel.hpp"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
		ConstPanel(IScalable *object, ISizing2 *sizing, IPositioning2 *positioning, bool displayed = false);
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		ConstPanel* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ConstPanel *&constPanel);
}
