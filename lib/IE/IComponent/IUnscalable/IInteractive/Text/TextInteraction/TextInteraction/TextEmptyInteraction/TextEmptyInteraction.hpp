#pragma once

#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	using TextEmptyInteraction = BasicEmptyInteraction<Text&>;
}