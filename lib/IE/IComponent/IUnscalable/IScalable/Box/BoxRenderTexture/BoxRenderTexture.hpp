#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxRenderTexture : public Box, public virtual IScalableObject, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			bool optimize = true;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, bool optimize = true, sf::Vector2f minSize = {});
			
			BoxRenderTexture* make(InitInfo initInfo) override;
		};
		
		BoxRenderTexture(Make&& make, InitInfo initInfo);
		
		BoxRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f minSize, InitInfo initInfo);
		
		BoxRenderTexture(BoxPtr<IScalable>&& object, bool optimize = true, sf::Vector2f minSize = {});
		
		BoxRenderTexture(const BoxRenderTexture& other);
		
		void init(InitInfo initInfo) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxRenderTexture* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		sf::RenderTexture renderTexture;
		sf::Sprite sprite;
		sf::View view;
		DrawManager drawManager;
		BoxPtr<IScalable> object;
		InteractionManager* interactionManager;
		sf::RenderTarget* renderTarget;
		bool optimize;
		bool active;
	};
	
	template<>
	struct DecodePointer<BoxRenderTexture> {
		static bool decodePointer(const YAML::Node& node, BoxRenderTexture*& boxWithRenderTexture);
	};
}
