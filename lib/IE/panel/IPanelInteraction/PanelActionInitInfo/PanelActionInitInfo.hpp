#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	using PanelActionInitInfo = BasicActionInitInfo<Panel&>;
}