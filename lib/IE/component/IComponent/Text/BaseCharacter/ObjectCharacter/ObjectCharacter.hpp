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
		
		ObjectCharacter(ObjectCharacter const& other);
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto resize(sf::Vector2f position, float end_position) -> void override;
		
		auto move(sf::Vector2f offset) -> void override;
		
		auto handle_event(Event event) -> bool;
		
		auto get_line() -> std::vector<BoxPtr<BaseLine::MainLine> > const& override;
		
		auto get_position() const -> sf::Vector2f override;
		
		auto get_size_texture() -> sf::Vector2i override;
		
		auto get_height() const -> float override;
		
		auto get_advance() -> float override;
		
		auto get_kerning(char32_t) -> float override;
		
		auto is_special() -> Special override;
		
		auto draw() -> void override;
		
		auto get_char() -> char32_t override;
		
		auto get_min_advance() -> float override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<IScalable> object_;
		std::vector<BoxPtr<BaseLine::MainLine> > lines_;
		BaseCharacter::Special special_;
	};
}