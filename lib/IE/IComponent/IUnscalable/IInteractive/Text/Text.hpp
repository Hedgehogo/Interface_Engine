#pragma once

#include "BaseTextBlock/BaseTextBlock.hpp"
#include "BaseResizer/Resizer/Resizer.hpp"
#include "../../IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp"
#include "TextInteraction/TextEvent/TextSelectionEvent/TextSelectionEvent.hpp"
#include "TextInteraction/TextInteraction/TextKeysInteraction/TextKeysInteraction.hpp"
#include "TextInteraction/TextEvent/TextCopyEvent/TextCopyEvent.hpp"
#include "TextInteraction/TextInteraction/TextEmptyInteraction/TextEmptyInteraction.hpp"
#include "TextInteraction/TextEvent/TextAddBlockInteractionEvent/TextAddBlockInteractionEvent.hpp"
#include "TextInteraction/TextInteraction/TextPressedInteraction/TextPressedInteraction.hpp"

namespace ie {
	class Text : public IInteractive, public IDrawable, public IUpdatable {
	protected:
		struct Selection {
			std::vector<BaseCharacter*>::iterator start;
			std::vector<BaseCharacter*>::iterator end;
		};
		
		void init(InitInfo initInfo) override;
	
	public:
		explicit Text(
			std::vector<BaseTextBlock*> textBlocks,
			IUninteractive* background = new FullColor(sf::Color::White),
			int size = 14,
			sf::Font* font = nullptr,
			sf::Color textColor = sf::Color::Black,
			sf::Color textSelectionColor = sf::Color::White,
			sf::Color backgroundSelectionColor = sf::Color::Blue,
			sf::Color inactiveTextSelectionColor = nullColor,
			sf::Color inactiveBackgroundSelectionColor = {150, 150, 150},
			BaseResizer* resizer = new Resizer{1.15, BaseResizer::Align::left},
			TextInteraction* textInteraction = new TextEmptyInteraction{}
		);
		
		~Text() override;
		
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
	
	protected:
		Text(
			std::vector<BaseTextBlock*> textBlocks, IUninteractive* background, uint size, BaseResizer* resizer, sf::RenderTarget* renderTarget,
			TextInteraction* textInteraction
		);
	
	public:
		Text* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		sf::RenderTarget* renderTarget;
		
		sf::RenderTexture renderTexture;
		sf::View view;
		sf::Texture texture;
		sf::Sprite sprite;
		DrawManager drawManager;
		
		bool interact;
		bool oldInteract;
		
		TextInteraction* textInteraction;
		
		Selection selection;
		
		uint size;
		
		std::vector<BaseCharacter*> textCharacters;
		std::vector<BaseTextBlock*> textBocks;
		std::vector<BaseLine*> lines;
		
		BaseResizer* resizer;
		
		IUninteractive* background;
	};
	
	template<>
	struct DecodePointer<Text> {
		static bool decodePointer(const YAML::Node& node, Text*& text);
	};
	
	extern std::vector<BaseCharacter*>::iterator nullBaseCharacterIterator;
}
