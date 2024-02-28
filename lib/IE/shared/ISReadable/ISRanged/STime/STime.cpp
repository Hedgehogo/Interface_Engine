#include "STime.hpp"
#include "IE/component/IUpdatable/UpdateManager/UpdateManager.hpp"

namespace ie {
	namespace make_system {
		STime::STime(
			MakeDyn<ISBool> start,
			orl::Option<MakeDyn<ISMBool> > end,
			float end_time,
			float data,
			bool pause_restart
		) : SRanged<float>(data),
			end_time(end_time),
			start(std::move(start)),
			end(std::move(end)),
			pause_restart(pause_restart) {
		}
		
		rttb::Dyn STime::make(SInitInfo init_info) {
			return rttb::Dyn{new ie::STime{std::move(*this), init_info}};
		}
	}
	
	STime::STime(
		STime::Make&& make,
		SInitInfo init_info
	) : SRanged(make.data, make.end_time, 0),
		delta_([&]() -> orl::Option<sf::Time> {
			if(make.pause_restart) {
				return {};
			}
			return sf::Time{};
		}()),
		end_(make.end.map([&](MakeDyn<ISMBool>& end) -> auto& {
			return DynBuffer::get(std::move(end), init_info);
		})),
		start_(DynBuffer::get(std::move(make.start), init_info), [&](const bool& start) {
			if(start) {
				clock_.restart();
			} else if(play_) {
				for(auto& delta: delta_) {
					delta += clock_.getElapsedTime();
				}
			}
			play_ = start;
		}),
		play_(start_.get().get()) {
		init_info.update_manager.add(*this);
	}
	
	void STime::update() {
		if(play_) {
			float data{clock_.getElapsedTime().asSeconds()};
			for(auto const& delta: delta_) {
				data += delta.asSeconds();
			}
			if(data_ < upper_bound_) {
				data_ = data;
			} else {
				play_ = false;
				data_ = 0;
				for(auto& delta: delta_) {
					delta = sf::Time{};
				}
				for(auto& end: end_) {
					end.set(true);
				}
			}
			reset();
		}
	}
}

orl::Option<ie::make_system::STime> ieml::Decode<char, ie::make_system::STime>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::make_system::STime{
		map.at("start").except().as<ie::MakeDyn<ie::ISBool> >().except(),
		map.get_as<orl::Option<ie::MakeDyn<ie::ISMBool> > >("end").except().ok_or({}),
		map.get_as<float>("end-time").except().ok_or(std::numeric_limits<float>::max()),
		map.get_as<float>("data").except().ok_or(0),
		map.get_as<bool>("pause-restart").except().ok_or(false),
	};
}