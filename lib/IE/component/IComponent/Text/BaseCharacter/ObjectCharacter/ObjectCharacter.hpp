#pragma once

#include "../BaseCharacter.hpp"
#include "../../../IScalable/IScalable.hpp"

namespace ie {
	class ObjectCharacter : public BaseCharacter {
	public:
		enum class ObjectSpecial {
			No,
			Object = static_cast<int>(BaseCharacter::Special::Object),
			FullLine,
		};
		
		explicit ObjectCharacter(BoxPtr<IScalable>&& object, ObjectSpecial special = ObjectSpecial::No);
		
		void set_position(sf::Vector2f position) override;
		
		void resize(sf::Vector2f position, float end_position) override;
		
		void move(sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position);
		
		const std::vector<BoxPtr<BaseLine>>& get_line() override;
		
		sf::Vector2f get_position() const override;
		
		sf::Vector2i get_size_texture() override;
		
		float get_height() const override;
		
		float get_advance() override;
		
		float get_kerning(char32_t) override;
		
		Special is_special() override;
		
		void draw() override;
		
		char32_t get_char() override;
		
		float get_min_advance() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<IScalable> object;
		std::vector<BoxPtr<BaseLine>> lines;
		BaseCharacter::Special special;
	};
}