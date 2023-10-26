#pragma once

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
		
		BoxRenderTexture(BoxPtr<IScalable>&& object, bool optimize = true, sf::Vector2f min_size = {});
		
		BoxRenderTexture(const BoxRenderTexture& other);
		
		void init(InitInfo init_info) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		BoxRenderTexture* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		sf::RenderTexture render_texture;
		sf::Sprite sprite;
		sf::View view;
		DrawManager draw_manager;
		BoxPtr<IScalable> object;
		InteractionManager* interaction_manager;
		sf::RenderTarget* render_target;
		bool optimize;
		bool active;
	};
	
	template<>
	struct DecodePointer<BoxRenderTexture> {
		static bool decode_pointer(const YAML::Node& node, BoxRenderTexture*& box_with_render_texture);
	};
}
