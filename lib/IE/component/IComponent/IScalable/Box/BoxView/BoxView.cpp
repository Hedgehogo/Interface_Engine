#include "BoxView.hpp"

namespace ie {
	BoxView::BoxView(sf::Vector2f min_size, InitInfo init_info) :
		Box(min_size), render_target_(&init_info.render_target) {
		init_info.draw_manager.add(*this);
	}
	
	BoxView::BoxView(sf::Vector2f min_size) : Box(min_size), render_target_(nullptr) {
	}
	
	auto BoxView::draw() -> void {
		auto old_view = render_target_->getView();
		render_target_->setView(view_);
		draw_manager_.draw();
		render_target_->setView(old_view);
	}
	
	auto BoxView::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		view_.setSize(size);
		view_.setCenter(position + (size / 2.f));
		
		sf::Vector2f render_target_size{render_target_->getSize()};
		view_.setViewport(
			{
				position.x / render_target_size.x,
				position.y / render_target_size.y,
				size.x / render_target_size.x,
				size.y / render_target_size.y
			}
		);
	}
}