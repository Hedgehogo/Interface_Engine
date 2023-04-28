#pragma once

#include "../box.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"

namespace ui {
	class BoxWithRenderTexture : public Box, public LayoutWithObject, public IDrawable {
	protected:
		InteractionManager* interactionManager;
		DrawManager drawManager;
		sf::RenderTarget* renderTarget;
		sf::RenderTexture renderTexture;
		sf::View view;
		sf::Sprite sprite;
		bool optimize;
		bool active;
		
		void copy(BoxWithRenderTexture* boxWithRenderTexture);
	
	public:
		void init(InitInfo initInfo) override;
		
		BoxWithRenderTexture(IScalable* object, bool optimize = true, sf::Vector2f minSize = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		BoxWithRenderTexture* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	
	template<>
	struct DecodePointer<BoxWithRenderTexture> {
		static bool decodePointer(const YAML::Node& node, BoxWithRenderTexture*& boxWithRenderTexture);
	};
	
	using BoxWRTexture = BoxWithRenderTexture;
	using BWRT = BoxWithRenderTexture;
}
