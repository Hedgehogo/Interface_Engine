#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/keys/keysInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
    class TextKeysInteraction : public TextInteraction, public KeysInteraction{
    public:
        TextKeysInteraction(KeyEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});

        void init(Text *text, InteractionManager &interactionManager) override;

        TextKeysInteraction * copy() override;

        ~TextKeysInteraction() = default;
    };

	bool convertPointer(const YAML::Node &node, TextKeysInteraction *&textKeysInteraction);
	
	template<>
	struct DecodePointer<TextKeysInteraction> {
		static bool decodePointer(const YAML::Node &node, TextKeysInteraction *&textKeysInteraction);
	};
}