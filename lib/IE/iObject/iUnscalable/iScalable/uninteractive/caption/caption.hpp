#pragma once

#include "../onlyDrawable/onlyDrawable.hpp"
#include "../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"
#include "../../../../../sizingAndPositioning/positioning2/internal/internalPositioning2.hpp"

namespace ui {
	class Caption : public OnlyDrawable {
	public:
		static void setDefaultColor(sf::Color color = sf::Color::White);
		
		static void setDefaultSize(int size);
		
		static sf::Color getDefaultColor();
		
		static int getDefaultSize();
		
		struct Make : public IUninteractive::Make {
			sf::String text;
			BoxPtr<IUninteractive::Make> background;
			sf::Font& font;
			int fontSize = defaultSize;
			sf::Color color = defaultColor;
			sf::Text::Style style = {};
			float rotation = 0;
			InternalPositioning2 positioning = {{0, 0}};
			bool cutBack = true;
			sf::Vector2f minSize = {};
			
			Make(
				sf::String text,
				BoxPtr<IUninteractive::Make>&& background,
				sf::Font& font,
				sf::Vector2f minSize,
				int fontSize = defaultSize,
				sf::Color color = defaultColor,
				sf::Text::Style style = {},
				float rotation = 0,
				InternalPositioning2 positioning = {{0, 0}},
				bool cutBack = true
			);
			
			Make(
				sf::String text,
				BoxPtr<IUninteractive::Make>&& background,
				sf::Font& font,
				int fontSize = defaultSize,
				sf::Color color = defaultColor,
				sf::Text::Style style = {},
				float rotation = 0,
				InternalPositioning2 positioning = {{0, 0}},
				bool cutBack = true
			);
			
			Caption* make(InitInfo initInfo) override;
		};
		
		Caption(Make&& make, InitInfo initInfo);
		
		Caption(
			sf::String text,
			BoxPtr<IUninteractive>&& background,
			sf::Font& font,
			sf::Vector2f minSize,
			int fontSize = defaultSize,
			sf::Color color = defaultColor,
			sf::Text::Style style = {},
			float rotation = 0,
			InternalPositioning2 positioning = {{0, 0}},
			bool cutBack = true
		);
		
		Caption(
			sf::String text,
			BoxPtr<IUninteractive>&& background,
			sf::Font& font,
			int fontSize = defaultSize,
			sf::Color color = defaultColor,
			sf::Text::Style style = {},
			float rotation = 0,
			InternalPositioning2 positioning = {{0, 0}},
			bool cutBack = true
		);
		
		void init(InitInfo initInfo) override;
		
		void draw() override;
		
		sf::FloatRect getBounds(const sf::Text& text) const;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		Caption* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		static sf::Color defaultColor;
		static int defaultSize;
		
		bool cutBack;
		
		sf::Text text;
		sf::String str;
		DrawManager drawManager;
		BoxPtr<IUninteractive> background;
		sf::Vector2f minimumSize;
		InternalPositioning2 positioning;
	};
	
	template<>
	struct DecodePointer<Caption> {
		static bool decodePointer(const YAML::Node& node, Caption*& caption);
	};
}
