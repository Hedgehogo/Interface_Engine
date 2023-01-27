#pragma once

#include "textBlock/baseTextBlock.hpp"
#include "resizer/simple/resizer.hpp"
#include "../../iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp"
#include "event/selection/textSelectionEvent.hpp"
#include "interaction/keys/textKeysInteraction.hpp"
#include "event/copy/textCopyEvent.hpp"
#include "interaction/empty/textEmptyInteraction.hpp"
#include "event/addBlockInteraction/textAddBlockInteractionEvent.hpp"
#include "interaction/block/pressed/textPressedInteraction.hpp"
#include "interaction/selectionAndCopy/textSelectionAndCopyInteraction.hpp"

namespace ui {
	class Text : public Interactive, public IDrawable, public IUpdatable {
    protected:
        sf::RenderTarget *renderTarget;

		sf::RenderTexture renderTexture;
		sf::View view;
		sf::Texture texture;
		sf::Sprite sprite;
		DrawManager drawManager;

        bool interact;
        bool oldInteract;

        TextInteraction* textInteraction;

        struct Selection {
            std::vector<BaseCharacter*>::iterator start;
            std::vector<BaseCharacter*>::iterator end;
        } selection;


        uint size;

        std::vector<BaseCharacter*> textCharacters;
        std::vector<BaseTextBlock*> textBocks;
        std::vector<BaseLine* > lines;

        BaseResizer* resizer;
		
        IUninteractive *background;
		
        void init(InteractiveInitInfo interactiveInitInfo) override;

    public:
        explicit Text(std::vector<BaseTextBlock *> textBlocks, IUninteractive *background = new FullColor(sf::Color::White), int size = 14, sf::Font *font = nullptr, sf::Color textColor = sf::Color::Black,
             sf::Color textSelectionColor = sf::Color::White, sf::Color backgroundSelectionColor = sf::Color::Blue, sf::Color inactiveTextSelectionColor = nullColor,
             sf::Color inactiveBackgroundSelectionColor = {150, 150, 150}, BaseResizer *resizer = new Resizer{1.15, BaseResizer::Align::left},
             TextInteraction *textInteraction =
				 new TextSelectionAndCopyInteraction{
					{
						{
							new TextPressedInteraction{
								new TextSelectionEvent{},
								{Key::mouseLeft}
							},
							{Key::mouseLeft}
						}
					},
					{
						new TextKeysInteraction{
							new TextCopyEvent{},
							{Key::c, Key::lControl}
						}
					}
				}
		);

        ~Text() override;

        void setSelection(Selection selection);
		
        void setSelectionStart(std::vector<BaseCharacter*>::iterator start);
		
        void setSelectionEnd(std::vector<BaseCharacter*>::iterator end);
		
        [[nodiscard]] Selection getSelection() const;
		
        [[nodiscard]] std::vector<BaseCharacter *>::iterator getSelectionStart() const;
		
        [[nodiscard]] std::vector<BaseCharacter *>::iterator getSelectionEnd() const;

        std::u32string getSelectionText();

        std::vector<BaseCharacter *>::iterator getCharacter(sf::Vector2f mousePosition);

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        void draw() override;

        void move(sf::Vector2f position) override;

        void setPosition(sf::Vector2f position) override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;
		
    protected:
        Text(std::vector<BaseTextBlock *> textBlocks, IUninteractive *background, uint size, BaseResizer *resizer, sf::RenderTarget *renderTarget,
             TextInteraction* textInteraction);
		
    public:
        Text *copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
    };
	
	bool convertPointer(const YAML::Node &node, Text *&text);

    extern std::vector<BaseCharacter *>::iterator nullBaseCharacterIterator;
}
