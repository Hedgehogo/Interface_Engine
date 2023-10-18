#pragma once

#include "../../../lib/IE/Interaction/IInteraction/IInteraction.hpp"
#include "../../../lib/IE/Interaction/InteractionManager/InteractionManager.hpp"


class TestInteraction : public ie::IInteraction {
public:
	struct Processed {
		struct Start {
			unsigned long long time{0};
			sf::Vector2i mouse_position;
		};
		struct Update {
			unsigned long long time{0};
			sf::Vector2i mouse_position;
		};
		struct Finish {
			unsigned long long time{0};
			sf::Vector2i mouse_position;
		};
		std::vector<Start> start;
		std::vector<Update> update;
		std::vector<Finish> finish;
		std::vector<unsigned long long> copy;
	};
	
	enum class Function {
		start,
		update,
		finish
	};

protected:
	Processed processed;
	Priority priority;
	bool blocked;

public:
	TestInteraction(Priority priority = Priority::medium, bool blocked = false);
	
	Processed get_processed();
	
	bool is_blocked() const override;
	
	Priority get_priority() const override;
	
	void start(sf::Vector2i mouse_position) override;
	
	void update(sf::Vector2i mouse_position) override;
	
	void finish(sf::Vector2i mouse_position) override;
	
	IInteraction* copy() override;
};
