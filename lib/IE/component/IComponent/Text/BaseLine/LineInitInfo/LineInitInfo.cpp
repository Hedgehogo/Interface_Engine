#include "LineInitInfo.hpp"

namespace ie {
	LineInitInfo::LineInitInfo(uint size, sf::Font& font, const sf::Color& color, sf::RenderTarget& render_target) : size(size), font(font), color(color), render_target(render_target) {
	}
}