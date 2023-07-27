#pragma once

#include "../iSValue.hpp"

namespace ui {
	template<typename T>
	class SValue : public virtual ISValue<T> {
	protected:
		T value;
		std::vector<typename ISValue<T>::SetterFunc> setters;
	
	public:
		explicit SValue(T value = T{});
		
		void addSetter(const typename ISValue<T>::SetterFunc& setter) override;
		
		const T& getValue() const override;
		
		void setValue(const T& value) override;
	};
	
	template<typename T>
	struct DecodePointer<SValue<T> > {
		static bool decodePointer(const YAML::Node& node, SValue<T>*& sValue);
	};
	
	typedef SValue<bool> Sbool;
	typedef SValue<float> Sfloat;
	typedef SValue<int> Sint;
	typedef SValue<unsigned> Suint;
	
	template<typename T>
	using PSValue = std::shared_ptr<SValue<T>>;
	
	typedef std::shared_ptr<Sbool> PSbool;
	typedef std::shared_ptr<Sfloat> PSfloat;
	typedef std::shared_ptr<Sint> PSint;
	typedef std::shared_ptr<Suint> PSuint;
}

#include "sValue.inl"