#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextEvent.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicAddInteractionEvent/BasicAddBlockInteractionEvent/BasicAddBlockInteractionEvent.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"

namespace ui {
	using TextAddBlockInteractionEvent = BasicAddBlockInteractionEvent<Text&>;
}