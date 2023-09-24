#pragma once

#include "IE/IComponent/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicKeysInteraction/BasicKeysInteraction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	using TextKeysInteraction = BasicKeysInteraction<Text&>;
}