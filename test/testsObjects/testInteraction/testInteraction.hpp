#pragma once

#include "../../../lib/IE/Interaction/IInteraction/IInteraction.hpp"
#include "../../../lib/IE/Interaction/InteractionManager/InteractionManager.hpp"


class TestInteraction : public ui::IInteraction {
public:
	struct Processed {
		struct Start {
			unsigned long long time{0};
			sf::Vector2i mousePosition;
		};
		struct Update {
			unsigned long long time{0};
			sf::Vector2i mousePosition;
		};
		struct Finish {
			unsigned long long time{0};
			sf::Vector2i mousePosition;
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
	
	Processed getProcessed();
	
	bool isBlocked() const override;
	
	Priority getPriority() const override;
	
	void start(sf::Vector2i mousePosition) override;
	
	void update(sf::Vector2i mousePosition) override;
	
	void finish(sf::Vector2i mousePosition) override;
	
	IInteraction* copy() override;
};
