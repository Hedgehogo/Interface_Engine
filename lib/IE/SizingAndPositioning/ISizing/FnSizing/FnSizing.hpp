#pragma once

#include "../ISizing.hpp"
#include <functional>

namespace ie {
	class FnSizing : public virtual ISizing {
	public:
		using FindSizeFn = std::function<float(float parentSize, float targetSize, float normalSize)>;
		using GetParentSizeFn = std::function<float(float objectMinSize)>;
		
		struct Make : public virtual ISizing::Make {
			FindSizeFn findSizeFn;
			GetParentSizeFn getParentSizeFn;
			
			Make() = default;
			
			Make(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn);
			
			FnSizing* make(float normalSize) override;
		};
		
		FnSizing(Make&& make, float normalSize);
		
		FnSizing(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn);
		
		void init(float normalSize) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectMinSize) override;
		
		FnSizing* copy() override;
	
	protected:
		FindSizeFn findSizeFn;
		GetParentSizeFn getParentSizeFn;
		float normalSize;
	};
}
