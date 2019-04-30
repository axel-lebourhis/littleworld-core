#include <SFML/Graphics.hpp>

#include "view.hpp"
#include "input.hpp"

class Controller {
	private:
		View* view_;
		Input input_;
	public:
		Controller(View*);

		void handleInputs();
};