#pragma once
#include "../../BaseCharacter/BaseCharacter.hpp"

namespace ie {
	struct TextResizerInitInfo {
		std::vector<BaseCharacter*>& characters;
	
		explicit TextResizerInitInfo(std::vector<BaseCharacter*>& characters);
	};
}
