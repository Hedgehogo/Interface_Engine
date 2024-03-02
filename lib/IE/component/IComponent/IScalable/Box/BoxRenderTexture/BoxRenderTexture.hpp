#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxRenderTexture : public Box, public virtual IScalableObject, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			bool optimize = true;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, bool optimize = true, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxRenderTexture* override;
		};
		
		BoxRenderTexture(Make&& make, InitInfo init_info);
		
		BoxRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f min_size, InitInfo init_info);
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		sf::RenderTexture render_texture_;
		sf::Sprite sprite_;
		sf::View view_;
		DrawManager draw_manager_;
		BoxPtr<IScalable> object_;
		InteractionManager* interaction_manager_;
		sf::RenderTarget* render_target_;
		bool optimize_;
		bool active_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxRenderTexture::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxRenderTexture::Make>;
};
