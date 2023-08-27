#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicKeyAction.hpp"
#include "../TextInteractionInitInfo/TextInteractionInitInfo.hpp"

namespace ie {
	class Text;
	
	using TextAction = BasicKeyAction<Text&>;
}