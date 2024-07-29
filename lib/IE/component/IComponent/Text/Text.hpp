#pragma once

#include "BaseTextBlock/BaseTextBlock.hpp"
#include "IE/component/IComponent/Text/BaseTextResizer/TextResizer/TextResizer.hpp"
#include "../IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "TextStyle/TextStyle.hpp"

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
			BoxPtr<INonInteractive::Make> background = make_box_ptr<FullColor::Make>(sf::Color::White);
			BoxPtr<BaseTextResizer::Make> resizer = make_box_ptr<TextResizer::Make>(1.15f, BaseTextResizer::Align::Left);
			BoxPtr<IBasicInteraction<Text&>::Make> text_interaction = make_box_ptr<BasicEmptyInteraction<Text&>::Make>();
			
			explicit Make(
				std::vector<BoxPtr<BaseTextBlock::Make> >&& text_blocks,
				BoxPtr<INonInteractive::Make>&& background = make_box_ptr<FullColor::Make>(sf::Color::White),
				BoxPtr<BaseTextResizer::Make>&& resizer = make_box_ptr<TextResizer::Make>(1.15f, BaseTextResizer::Align::Left),
				BoxPtr<IBasicInteraction<Text&>::Make>&& text_interaction = make_box_ptr<BasicEmptyInteraction<Text&>::Make>()
			);
			
			auto make(InitInfo init_info) -> Text* override;
		};
		
		Text(Make&& make, InitInfo init_info);
		
		auto set_selection(Selection selection) -> void;
		
		auto set_selection_start(orl::Option<std::vector<BaseCharacter*>::iterator> start) -> void;
		
		auto set_selection_end(orl::Option<std::vector<BaseCharacter*>::iterator> end) -> void;
		
		[[nodiscard]] auto get_selection() const -> Selection;
		
		[[nodiscard]] auto get_selection_start() const -> std::vector<BaseCharacter*>::iterator;
		
		[[nodiscard]] auto get_selection_end() const -> std::vector<BaseCharacter*>::iterator;
		
		auto get_selection_text() -> sf::String;
		
		auto get_characters() -> std::vector<BaseCharacter*>&;
		
		auto get_character(sf::Vector2f point_position) -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto update() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto draw() -> void override;
		
		auto move(sf::Vector2f offset) -> void override;
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		InteractionManager* interaction_manager;
		sf::RenderTarget* render_target;
		
		sf::RenderTexture render_texture;
		sf::View view;
		sf::Texture texture;
		sf::Sprite sprite;
		DrawManager draw_manager;
		
		BoxPtr<INonInteractive> background;
		
		Selection selection;
		
		std::vector<BaseCharacter*> text_characters;
		std::vector<BoxPtr<BaseTextBlock> > text_blocks;
		
		BoxPtr<BaseTextResizer> resizer;
		BoxPtr<IBasicInteraction<Text&> > text_interaction;
	};
}

template<>
struct ieml::Decode<char, ie::Text::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Text::Make>;
};