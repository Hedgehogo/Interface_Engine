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
			
			BoxRenderTexture* make(InitInfo init_info) override;
		};
		
		BoxRenderTexture(Make&& make, InitInfo init_info);
		
		BoxRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f min_size, InitInfo init_info);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
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
	static orl::Option<ie::BoxRenderTexture::Make> decode(ieml::Node const& node);
};
