#pragma once
#include "../../BaseCharacter/BaseCharacter.hpp"

namespace ie {
	struct ResizerInitInfo {
		std::vector<BaseCharacter*>& characters;
		std::vector<BoxPtr<BaseLine>>& lines;
	
		ResizerInitInfo(std::vector<BaseCharacter*>& characters, std::vector<BoxPtr<BaseLine>>& lines);
	};
}
