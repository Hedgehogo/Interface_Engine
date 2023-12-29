#pragma once
#include "../../BaseCharacter/BaseCharacter.hpp"

namespace ie {
	struct ResizerInitInfo {
		std::vector<BaseCharacter*>& characters;
	
		explicit ResizerInitInfo(std::vector<BaseCharacter*>& characters);
	};
}
