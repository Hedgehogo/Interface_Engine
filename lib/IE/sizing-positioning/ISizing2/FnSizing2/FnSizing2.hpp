#pragma once

#include "../ISizing2.hpp"
#include <functional>

namespace ie {
	class FnSizing2 : public virtual ISizing2 {
	public:
		using FindSizeFn = std::function<sf::Vector2f(sf::Vector2f parent_size, sf::Vector2f target_size, sf::Vector2f normal_size)>;
		using GetParentSizeFn = std::function<sf::Vector2f(sf::Vector2f object_min_size)>;
		
		struct Make : public virtual ISizing2::Make {
			FindSizeFn find_size_fn;
			GetParentSizeFn get_parent_size_fn;
			
			Make() = default;
			
			Make(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn);
			
			FnSizing2* make(Sizing2InitInfo init_info) override;
		};
		
		FnSizing2(Make&& make, Sizing2InitInfo init_info);
		
		FnSizing2(FindSizeFn find_size_fn, GetParentSizeFn get_parent_size_fn);
		
		void init(sf::RenderTarget& render_target, sf::Vector2f normal_size) override;
		
		sf::Vector2f find_size(sf::Vector2f parent_size) override;
		
		sf::Vector2f get_parent_size(sf::Vector2f object_size) override;
		
		FnSizing2* copy() override;
	
	protected:
		FindSizeFn find_size_fn;
		GetParentSizeFn get_parent_size_fn;
		sf::RenderTarget* render_target;
		sf::Vector2f normal_size;
	};
}
