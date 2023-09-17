#pragma once

#include "../../value/range/sRangeValue.hpp"
#include "../iSVector2.hpp"

namespace ie {
	template<typename T>
	class SVector2 : public virtual ISVector2 {
	protected:
		void set();
	
	public:
		using V = to_auto<decltype(std::declval<T>().getValue())>;
		using SetterFunc = std::function<void(const sf::Vector2<V>&)>;
		
		SVector2(const sf::Vector2<V>& vector = {});
		
		SVector2(std::shared_ptr<T> x, std::shared_ptr<T> y);
		
		virtual void addSetter(const SetterFunc& setter);
		
		PIShared getXPtr() const override;
		
		void setXPtr(PIShared value) override;
		
		PIShared getYPtr() const override;
		
		void setYPtr(PIShared value) override;
		
		V getX() const;
		
		void setX(const V& value);
		
		V getY() const;
		
		void setY(const V& value);
		
		sf::Vector2<V> getValue() const;
		
		void setValue(const sf::Vector2<V>& vector);
	
	protected:
		std::shared_ptr<T> x, y;
		std::vector<SetterFunc> setters;
	};
	
	template<typename T>
	struct DecodePointer<SVector2<T> > {
		static bool decodePointer(const YAML::Node& node, SVector2<T>*& withVector2);
	};
	
	template<typename T>
	using SVec2 = SVector2<T>;
	
	template<typename T>
	using PSVec2 = std::shared_ptr<SVec2<T> >;
	
	template<typename T>
	void setRangeUpper(PSVec2<SRange<T> > value, sf::Vector2<T> upper);
	
	template<typename T>
	void setRangeLower(PSVec2<SRange<T> > value, sf::Vector2<T> lower);
	
	template<typename T>
	void setRangeBounds(PSVec2<SRange<T> > value, sf::Vector2<T> lower, sf::Vector2<T> upper);
	
	using SVec2f = SVec2<Sfloat>;
	using SVec2i = SVec2<Sint>;
	using SVec2u = SVec2<Suint>;
	using SRVec2f = SVec2<SRfloat>;
	using SRVec2i = SVec2<SRint>;
	using SRVec2u = SVec2<SRuint>;
	using SCoefficientVec2 = SVec2<SCoefficientValue>;
	
	using PSVec2f = std::shared_ptr<SVec2f>;
	using PSVec2i = std::shared_ptr<SVec2i>;
	using PSVec2u = std::shared_ptr<SVec2u>;
	using PSRVec2f = std::shared_ptr<SRVec2f>;
	using PSRVec2i = std::shared_ptr<SRVec2i>;
	using PSRVec2u = std::shared_ptr<SRVec2u>;
	using PSCoefficientVec2 = std::shared_ptr<SCoefficientVec2>;
}

#include "sVector2.inl"
