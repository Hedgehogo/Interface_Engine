#pragma once

#include "../ISValue.hpp"

namespace ie {
	template<typename T>
	class SReferenceValue : public virtual ISValue<T> {
	public:
		explicit SReferenceValue(T& valueReference);
		
		void addSetter(const typename ISValue<T>::SetterFunc& setter) override;
		
		const T& getValue() const override;
		
		void setValue(const T& value) override;
		
		virtual void setReference(T& valueReference);
	
	protected:
		T* valueReference;
		std::vector<typename ISValue<T>::SetterFunc> setters;
	};
}

#include "SReferenceValue.inl"
