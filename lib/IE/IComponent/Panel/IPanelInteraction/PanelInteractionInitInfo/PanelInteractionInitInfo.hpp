#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/Interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	using PanelInteractionInitInfo = BasicActionInitInfo<Panel&>;
}
