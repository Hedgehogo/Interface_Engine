#pragma once

#include "IE/iObject/iUnscalable/interactive/text/Interaction/Interaction/textInteraction.hpp"
#include "IE/Interaction/IInteraction/KeysInteraction/KeysInteraction.hpp"
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