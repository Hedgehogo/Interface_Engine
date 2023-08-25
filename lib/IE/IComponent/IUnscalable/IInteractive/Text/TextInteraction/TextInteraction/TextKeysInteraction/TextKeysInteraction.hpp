#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicKeysInteraction/BasicKeysInteraction.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	using TextKeysInteraction = BasicKeysInteraction<Text&>;
}