#pragma once

#include "../baseInteractive.hpp"
#include "../../../uninteractive/uninteractive.hpp"

namespace ui {
	class BaseButton : public BaseInteractive {
	public:
		BaseButton(BoxPtr<IScalable::Make>&& background, BoxPtr<IInteraction>&& interaction, InitInfo initInfo);
		
		BaseButton(BoxPtr<IScalable>&& background, BoxPtr<IInteraction>&& interaction);
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		const IScalable& getBackground() const;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> background;
	};
}