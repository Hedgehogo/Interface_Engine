#include "BoxView.hpp"

namespace ie {
	BoxWithView::BoxWithView(sf::Vector2f min_size, InitInfo init_info) :
		Box(min_size), render_target(&init_info.render_target) {
		init_info.draw_manager.add(*this);
	}
	
	BoxWithView::BoxWithView(sf::Vector2f min_size) : Box(min_size), render_target(nullptr) {
	}
	
	BoxWithView::BoxWithView(const BoxWithView& other) :
		Box(other), render_target(other.render_target), view(other.view) {
	}
	
	void BoxWithView::init(InitInfo init_info) {
		this->render_target = &init_info.render_target;
		init_info.draw_manager.add(*this);
	}
	
	void BoxWithView::draw() {
		sf::View old_view = render_target->getView();
		render_target->setView(view);
		draw_manager.draw();
		render_target->setView(old_view);
	}
	
	void BoxWithView::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		view.setSize(size);
		view.setCenter(position + (size / 2.f));
		
		sf::Vector2f render_target_size{render_target->getSize()};
		view.setViewport(
			{
				position.x / render_target_size.x,
				position.y / render_target_size.y,
				size.x / render_target_size.x,
				size.y / render_target_size.y
			}
		);
	}
}