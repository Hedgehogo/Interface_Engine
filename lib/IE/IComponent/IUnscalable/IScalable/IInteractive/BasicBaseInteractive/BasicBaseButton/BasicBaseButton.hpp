#pragma once

#include "../BasicBaseInteractive.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicBaseButton : public BasicBaseInteractive<T> {
	public:
		BasicBaseButton(BoxPtr<IScalable::Make>&& background, BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional);
		
		BasicBaseButton(BoxPtr<IScalable>&& background, BoxPtr<IBasicInteraction<T> >&& interaction);
		
		void init(InitInfo initInfo, T additional) override;
		
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
	
	using BaseButton = BasicBaseButton<>;
}

#include "BasicBaseButton.inl"
