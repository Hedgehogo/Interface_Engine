#pragma once

#include "../iSizing.hpp"

namespace ui {
	class ConstSizing : public ISizing {
	public:
		ConstSizing(float size);
		
		void init(float) override;
		
		float findSize(float, float) override;
		
		ConstSizing* copy() override;
	
	protected:
		float size;
	};
	
	template<>
	struct DecodePointer<ConstSizing> {
		static bool decodePointer(const YAML::Node& node, ConstSizing*& constSizing);
	};
}
