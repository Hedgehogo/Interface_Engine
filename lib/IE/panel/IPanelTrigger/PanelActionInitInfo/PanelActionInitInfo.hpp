#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/trigger/BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	using PanelActionInitInfo = BasicActionInitInfo<Panel&>;
}