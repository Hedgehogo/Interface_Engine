#pragma once

#include "../baseButton.hpp"

namespace ui {
	class Button : public BaseButton {
	public:
		Button(BoxPtr<IScalable>&& background, std::size_t interaction);
		
		Button(BoxPtr<IScalable>&& background, BoxPtr<IInteraction>&& interaction);
		
		~Button() override;
		
		void init(InitInfo initInfo) override;
		
		Button* copy() override;
	
	protected:
		std::size_t interactionIndex;
	};
	
	template<>
	struct DecodePointer<Button> {
		static bool decodePointer(const YAML::Node& node, Button*& button);
	};
}
