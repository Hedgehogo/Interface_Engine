#include "LineInitInfo.hpp"

namespace ie {
	LineInitInfo::LineInitInfo(uint size, sf::Font& font, const sf::Color& color, sf::RenderTarget& renderTarget) : size(size), font(font), color(color), renderTarget(renderTarget) {
	}
}