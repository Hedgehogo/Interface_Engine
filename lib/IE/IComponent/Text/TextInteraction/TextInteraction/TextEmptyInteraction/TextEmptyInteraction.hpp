#pragma once

#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "IE/IComponent/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	using TextEmptyInteraction = BasicEmptyInteraction<Text&>;
}