#pragma once

#include "BaseTextBlock/BaseTextBlock.hpp"
#include "IE/component/IComponent/Text/BaseTextResizer/TextResizer/TextResizer.hpp"
#include "../IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"

namespace ie {
	class Text : public virtual IComponent, public virtual IDrawable, public virtual IUpdatable {
	protected:
		struct Selection {
			orl::Option<std::vector<BaseCharacter*>::iterator> start;
			orl::Option<std::vector<BaseCharacter*>::iterator> end;
		};
		
	public:
		struct Make : public virtual IComponent::Make {
			std::vector<BoxPtr<BaseTextBlock::Make> > text_blocks;
			sf::Font& font;
			BoxPtr<INonInteractive::Make> background = make_box_ptr<FullColor::Make>(sf::Color::White);
			size_t size = 14;
			sf::Color text_color = sf::Color::Black;
			sf::Color text_selection_color = sf::Color::White;
			sf::Color background_selection_color = sf::Color::Blue;
			sf::Color inactive_text_selection_color = sf::Color::Black;
			sf::Color inactive_background_selection_color = {150, 150, 150};
			sf::Text::Style style = {};
			BoxPtr<BaseTextResizer::Make> resizer = make_box_ptr<TextResizer::Make>(1.15f, BaseTextResizer::Align::Left);
			BoxPtr<IBasicInteraction<Text&>::Make> text_interaction = make_box_ptr<BasicEmptyInteraction<Text&>::Make>();
			
			explicit Make(
				std::vector<BoxPtr<BaseTextBlock::Make> >&& text_blocks,
				sf::Font& font,
				BoxPtr<INonInteractive::Make>&& background = make_box_ptr<FullColor::Make>(sf::Color::White),
				size_t size = 14,
				sf::Color text_color = sf::Color::Black,
				sf::Color text_selection_color = sf::Color::White,
				sf::Color background_selection_color = sf::Color::Blue,
				sf::Color inactive_text_selection_color = sf::Color::Black,
				sf::Color inactive_background_selection_color = {150, 150, 150},
				sf::Text::Style style = {},
				BoxPtr<BaseTextResizer::Make>&& resizer = make_box_ptr<TextResizer::Make>(1.15f, BaseTextResizer::Align::Left),
				BoxPtr<IBasicInteraction<Text&>::Make>&& text_interaction = make_box_ptr<BasicEmptyInteraction<Text&>::Make>()
			);
			
			Text* make(InitInfo init_info) override;
		};
		
		Text(Make&& make, InitInfo init_info);
		
		void set_selection(Selection selection);
		
		void set_selection_start(orl::Option<std::vector<BaseCharacter*>::iterator> start);
		
		void set_selection_end(orl::Option<std::vector<BaseCharacter*>::iterator> end);
		
		[[nodiscard]] Selection get_selection() const;
		
		[[nodiscard]] std::vector<BaseCharacter*>::iterator get_selection_start() const;
		
		[[nodiscard]] std::vector<BaseCharacter*>::iterator get_selection_end() const;
		
		sf::String get_selection_text();
		
		std::vector<BaseCharacter*>& get_characters();
		
		orl::Option<std::vector<BaseCharacter*>::iterator> get_character(sf::Vector2f mouse_position);
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void draw() override;
		
		void move(sf::Vector2f position) override;
		
		void set_position(sf::Vector2f position) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		InteractionManager* interaction_manager;
		sf::RenderTarget* render_target;
		
		sf::RenderTexture render_texture;
		sf::View view;
		sf::Texture texture;
		sf::Sprite sprite;
		DrawManager draw_manager;
		
		BoxPtr<INonInteractive> background;
		
		bool interact;
		bool old_interact;
		Selection selection;
		size_t size;
		
		std::vector<BaseCharacter*> text_characters;
		std::vector<BoxPtr<BaseTextBlock> > text_blocks;
		
		BoxPtr<BaseTextResizer> resizer;
		BoxPtr<IBasicInteraction<Text&> > text_interaction;
	};
}

template<>
struct ieml::Decode<char, ie::Text::Make> {
	static orl::Option<ie::Text::Make> decode(ieml::Node const& node);
};