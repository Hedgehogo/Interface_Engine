#pragma once

#include "../../../lib/ui/interaction/iInteraction/iInteraction.hpp"
#include "../../../lib/ui/interaction/interactionManager/interactionManager.hpp"

class TestInteraction : public ui::IInteraction{
public:
	struct Processed{
		struct Start{
			uint64_t time{0};
			sf::Vector2i mousePosition;
		};
		struct Update{
			uint64_t time{0};
			sf::Vector2i mousePosition;
		};
		struct Finish{
			uint64_t time{0};
			sf::Vector2i mousePosition;
		};
		std::vector<Start> start;
		std::vector<Update> update;
		std::vector<Finish> finish;
		std::vector<uint64_t> copy;
	};

	enum class Function{
		start,
		update,
		finish
	};

protected:
	Priority priority;
	Processed processed;
	bool updateResult;

	TestInteraction* testInteraction;

public:
	TestInteraction(Priority priority = Priority::medium, bool blocked = false);

	Processed getProcessed();

	void start(sf::Vector2i mousePosition) override;

	bool update(sf::Vector2i mousePosition) override;

	void finish(sf::Vector2i mousePosition) override;

	IInteraction *copy() override;
};
