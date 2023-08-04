#pragma once

#include "../../../interactive/interactive.hpp"

namespace ui {
	class Interactive_Simple : public virtual IScalable, public Interactive, public IUpdatable {
	public:
		explicit Interactive_Simple(BoxPtr<IInteraction>&& interaction);
		
		void init(InitInfo initInfo) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	
	protected:
		BoxPtr<IInteraction> interaction;
	
	private:
		bool interact;
		bool oldInteract;
	};
}
