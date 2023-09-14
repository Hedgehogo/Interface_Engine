#pragma once

#include "BaseTextBlock/BaseTextBlock.hpp"
#include "BaseResizer/Resizer/Resizer.hpp"
#include "../IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp"
#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

namespace ie {
	class Text : public virtual IUnscalable, public virtual IDrawable, public virtual IUpdatable {
	protected:
		struct Selection {
			std::vector<BaseCharacter*>::iterator start;
			std::vector<BaseCharacter*>::iterator end;
		};
		
		void init(InitInfo initInfo) override;
	
	public:
		explicit Text(
			std::vector<BoxPtr<BaseTextBlock>>&& textBlocks,
			BoxPtr<IUninteractive>&& background = makeBoxPtr<FullColor>(sf::Color::White),
			int size = 14,
			sf::Font* font = nullptr,
			sf::Color textColor = sf::Color::Black,
			sf::Color textSelectionColor = sf::Color::White,
			sf::Color backgroundSelectionColor = sf::Color::Blue,
			sf::Color inactiveTextSelectionColor = nullColor,
			sf::Color inactiveBackgroundSelectionColor = {150, 150, 150},
			BoxPtr<BaseResizer>&& resizer = makeBoxPtr<Resizer>(1.15f, BaseResizer::Align::left),
			BoxPtr<IBasicInteraction<Text&>>&& textInteraction = makeBoxPtr<BasicEmptyInteraction<Text&>>()
		);
		
		void setSelection(Selection selection);
		
		void setSelectionStart(std::vector<BaseCharacter*>::iterator start);
		
		void setSelectionEnd(std::vector<BaseCharacter*>::iterator end);
		
		[[nodiscard]] Selection getSelection() const;
		
		[[nodiscard]] std::vector<BaseCharacter*>::iterator getSelectionStart() const;
		
		[[nodiscard]] std::vector<BaseCharacter*>::iterator getSelectionEnd() const;
		
		std::u32string getSelectionText();
		
		std::vector<BaseCharacter*>::iterator getCharacter(sf::Vector2f mousePosition);
		
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
		
		bool interact;
		bool oldInteract;
		
		BoxPtr<IBasicInteraction<Text&> > textInteraction;
		
		Selection selection;
		
		uint size;
		
		std::vector<BaseCharacter*> textCharacters;
		std::vector<BoxPtr<BaseTextBlock> > textBlocks;
		std::vector<BoxPtr<BaseLine> > lines;
		
		BoxPtr<BaseResizer> resizer;
		
		BoxPtr<IUninteractive> background;
	};
	
	template<>
	struct DecodePointer<Text> {
		static bool decodePointer(const YAML::Node& node, Text*& text);
	};
	
	extern std::vector<BaseCharacter*>::iterator nullBaseCharacterIterator;
}
