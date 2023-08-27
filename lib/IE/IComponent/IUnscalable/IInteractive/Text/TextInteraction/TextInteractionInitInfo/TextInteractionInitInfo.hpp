#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/Interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	class Text;
	
	using TextInteractionInitInfo = BasicActionInitInfo<Text&>;
}
