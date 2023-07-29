#pragma once

#include "../box.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"

namespace ui {
	class BoxWithRenderTexture : public Box, public ILayoutWithObject, public IDrawable {
	protected:
		void copy(BoxWithRenderTexture* boxWithRenderTexture);
	
	public:
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
		BoxPtr<IScalable> object;
		InteractionManager* interactionManager;
		DrawManager drawManager;
		sf::RenderTarget* renderTarget;
		sf::RenderTexture renderTexture;
		sf::View view;
		sf::Sprite sprite;
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
