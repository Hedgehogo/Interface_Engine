#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicKeyEvent.hpp"
#include "../TextInteractionInitInfo/TextInteractionInitInfo.hpp"

namespace ie {
	class Text;
	
	using TextEvent = BasicKeyEvent<Text&>;
}