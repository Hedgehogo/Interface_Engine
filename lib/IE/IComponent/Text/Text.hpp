#pragma once

#include "BaseTextBlock/BaseTextBlock.hpp"
#include "BaseResizer/Resizer/Resizer.hpp"
#include "../IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp"
#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

namespace ie {
	class Text : public virtual IComponent, public virtual IDrawable, public virtual IUpdatable {
	protected:
		struct Selection {
			orl::Option<std::vector<BaseCharacter*>::iterator> start;
			orl::Option<std::vector<BaseCharacter*>::iterator> end;
		};
		
	public:
		struct Make : public virtual IComponent::Make {
			std::vector<BoxPtr<BaseTextBlock::Make> > textBlocks;
			BoxPtr<IUninteractive::Make> background = makeBoxPtr<FullColor::Make>(sf::Color::White);
			uint size = 14;
			orl::Option<sf::Font*> font = {};
			sf::Color textColor = sf::Color::Black;
			sf::Color textSelectionColor = sf::Color::White;
			sf::Color backgroundSelectionColor = sf::Color::Blue;
			sf::Color inactiveTextSelectionColor = sf::Color::Black;
			sf::Color inactiveBackgroundSelectionColor = {150, 150, 150};
			sf::Text::Style style = {};
			BoxPtr<BaseResizer::Make> resizer = makeBoxPtr<Resizer::Make>(1.15f, BaseResizer::Align::Left);
			BoxPtr<IBasicInteraction<Text&>::Make> textInteraction = makeBoxPtr<BasicEmptyInteraction<Text&>::Make>();
			
			explicit Make(std::vector<BoxPtr<BaseTextBlock::Make> >&& textBlocks,
				BoxPtr<IUninteractive::Make>&& background = makeBoxPtr<FullColor::Make>(sf::Color::White),
				uint size = 14,
				orl::Option<sf::Font*> font = {},
				sf::Color textColor = sf::Color::Black,
				sf::Color textSelectionColor = sf::Color::White,
				sf::Color backgroundSelectionColor = sf::Color::Blue,
				sf::Color inactiveTextSelectionColor = sf::Color::Black,
				sf::Color inactiveBackgroundSelectionColor = {150, 150, 150},
				sf::Text::Style style = {},
				BoxPtr<BaseResizer::Make>&& resizer = makeBoxPtr<Resizer::Make>(1.15f, BaseResizer::Align::Left),
				BoxPtr<IBasicInteraction<Text&>::Make>&& textInteraction = makeBoxPtr<BasicEmptyInteraction<Text&>::Make>()
			);
			
			Text* make(InitInfo initInfo) override;
		};
		
		Text(Make&& make, InitInfo initInfo);
		
		explicit Text(std::vector<BoxPtr<BaseTextBlock> >&& textBlocks,
			BoxPtr<IUninteractive>&& background = makeBoxPtr<FullColor>(sf::Color::White),
			int size = 14,
			orl::Option<sf::Font*> font = {},
			sf::Color textColor = sf::Color::Black,
			sf::Color textSelectionColor = sf::Color::White,
			sf::Color backgroundSelectionColor = sf::Color::Blue,
			sf::Color inactiveTextSelectionColor = sf::Color::Black,
			sf::Color inactiveBackgroundSelectionColor = {150, 150, 150},
			sf::Text::Style style = {},
			BoxPtr<BaseResizer>&& resizer = makeBoxPtr<Resizer>(1.15f, BaseResizer::Align::Left),
			BoxPtr<IBasicInteraction<Text&>>&& textInteraction = makeBoxPtr<BasicEmptyInteraction<Text&>>()
		);
		
		void init(InitInfo initInfo) override;
		
		void setSelection(Selection selection);
		
		void setSelectionStart(orl::Option<std::vector<BaseCharacter*>::iterator> start);
		
		void setSelectionEnd(orl::Option<std::vector<BaseCharacter*>::iterator> end);
		
		[[nodiscard]] Selection getSelection() const;
		
		[[nodiscard]] std::vector<BaseCharacter*>::iterator getSelectionStart() const;
		
		[[nodiscard]] std::vector<BaseCharacter*>::iterator getSelectionEnd() const;
		
		std::u32string getSelectionText();
		
		orl::Option<std::vector<BaseCharacter*>::iterator> getCharacter(sf::Vector2f mousePosition);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void draw() override;
		
		void move(sf::Vector2f position) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		Text* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		InteractionManager* interactionManager;
		sf::RenderTarget* renderTarget;
		
		sf::RenderTexture renderTexture;
		sf::View view;
		sf::Texture texture;
		sf::Sprite sprite;
		DrawManager drawManager;
		
		BoxPtr<IUninteractive> background;
		
		bool interact;
		bool oldInteract;
		Selection selection;
		uint size;
		
		std::vector<BaseCharacter*> textCharacters;
		std::vector<BoxPtr<BaseTextBlock> > textBlocks;
		std::vector<BoxPtr<BaseLine> > lines;
		
		BoxPtr<BaseResizer> resizer;
		BoxPtr<IBasicInteraction<Text&> > textInteraction;
	};
	
	template<>
	struct DecodePointer<Text> {
		static bool decodePointer(const YAML::Node& node, Text*& text);
	};
}
