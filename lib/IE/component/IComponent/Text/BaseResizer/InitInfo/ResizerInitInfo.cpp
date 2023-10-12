#include "ResizerInitInfo.hpp"

namespace ie {
	ResizerInitInfo::ResizerInitInfo(std::vector<BaseCharacter*>& characters, std::vector<BoxPtr<BaseLine>>& lines) : characters(characters), lines(lines) {
	}
}