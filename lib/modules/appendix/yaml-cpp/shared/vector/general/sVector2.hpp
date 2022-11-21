#pragma once
#include "../iSVector2.hpp"

namespace ui {
	template<typename T>
	class SVector2 : public ISVector2 {
	public:
		typedef to_auto<decltype(std::declval<T>().getValue())> V;
		using SetterFunc = std::function<void(const sf::Vector2<V>&)>;
	
	protected:
		std::shared_ptr<T> x, y;
		std::vector<SetterFunc> setters;
		
		void set();
	
	public:
		SVector2(const sf::Vector2<V> &vector = {});
		
		SVector2(std::shared_ptr<T> x, std::shared_ptr<T> y);
		
		virtual void addSetter(const SetterFunc& setter);
		
		PIShared getXPtr() const override;
		
		void setXPtr(PIShared value) override;
		
		PIShared getYPtr() const override;
		
		void setYPtr(PIShared value) override;
		
		V getX() const;
		
		void setX(const V &value);
		
		V getY() const;
		
		void setY(const V &value);
		
		sf::Vector2<V> getValue() const;
		
		void setValue(const sf::Vector2<V> &vector);
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SVector2<T> *&withVector2);
	
	template <typename T>
	using SVec2 = SVector2<T>;
	
	template <typename T>
	using PSVec2 = std::shared_ptr<SVec2<T>>;
	
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
