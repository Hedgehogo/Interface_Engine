#pragma once

#include "IE/Interaction/IInteraction/IInteraction.hpp"
#include "../TextInteractionInitInfo/TextInteractionInitInfo.hpp"

namespace ui {
	class Text;
	
	using TextInteraction = IBasicInteraction<Text&>;
}