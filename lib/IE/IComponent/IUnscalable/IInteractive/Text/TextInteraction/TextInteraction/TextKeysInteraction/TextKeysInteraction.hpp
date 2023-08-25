#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicKeysInteraction/BasicKeysInteraction.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextKeysInteraction : public TextInteraction, public KeysInteraction {
	public:
		TextKeysInteraction(BoxPtr<KeyEvent> event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		void init(TextInteractionInitInfo textInteractionInitInfo) override;
		
		TextKeysInteraction* copy() override;
		
		~TextKeysInteraction() = default;
	};
	
	template<>
	struct DecodePointer<TextKeysInteraction> {
		static bool decodePointer(const YAML::Node& node, TextKeysInteraction*& textKeysInteraction);
	};
}