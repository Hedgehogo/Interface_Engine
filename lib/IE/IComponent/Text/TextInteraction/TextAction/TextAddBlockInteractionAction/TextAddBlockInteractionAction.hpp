#pragma once

#include "IE/IComponent/Text/TextInteraction/TextAction/TextAction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "IE/IComponent/Text/TextInteraction/TextInteraction/TextInteraction.hpp"

namespace ie {
	using TextAddBlockInteractionAction = BasicAddBlockInteractionAction<Text&>;
}