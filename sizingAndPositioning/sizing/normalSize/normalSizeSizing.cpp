#include "normalSizeSizing.h"

namespace ui {
	NormalSizeSizing::NormalSizeSizing() : size(0) {}
	
	void NormalSizeSizing::init(sf::RenderTarget &, float normalSize) {
		this->size = normalSize;
	}
	
	float NormalSizeSizing::findSize(float) {
		return this->size;
	}
	
	void NormalSizeSizing::copy(NormalSizeSizing *normalSizeSizing) {
		normalSizeSizing->size = this->size;
	}
	
	NormalSizeSizing *NormalSizeSizing::copy() {
		NormalSizeSizing* normalSizeSizing{new NormalSizeSizing{}};
		NormalSizeSizing::copy(normalSizeSizing);
		return normalSizeSizing;
	}
	
	Sizing *createSize() {
		return new NormalSizeSizing{};
	}
}