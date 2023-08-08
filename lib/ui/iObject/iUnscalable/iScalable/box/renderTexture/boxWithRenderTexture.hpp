#pragma once

#include "../box.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"

namespace ui {
	class BoxWithRenderTexture : public Box, public ILayoutWithObject, public IDrawable {
	public:
		struct Make : public Box::Make, public ILayoutWithObject::Make {
			BoxPtr<IScalable::Make> object;
			bool optimize = true;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, bool optimize = true, sf::Vector2f minSize = {});
			
			BoxWithRenderTexture* make(InitInfo initInfo) override;
		};
		
		BoxWithRenderTexture(Make&& make, InitInfo initInfo);
		
		BoxWithRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f minSize, InitInfo initInfo);
		
		BoxWithRenderTexture(BoxPtr<IScalable>&& object, bool optimize = true, sf::Vector2f minSize = {});
		
		BoxWithRenderTexture(const BoxWithRenderTexture& other);
		
		void init(InitInfo initInfo) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxWithRenderTexture* copy() override;
		
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
	struct DecodePointer<BoxWithRenderTexture> {
		static bool decodePointer(const YAML::Node& node, BoxWithRenderTexture*& boxWithRenderTexture);
	};
	
	using BoxWRTexture = BoxWithRenderTexture;
	using BWRT = BoxWithRenderTexture;
}
