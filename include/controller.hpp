#include <SFML/Graphics.hpp>

#include "view.hpp"
#include "model.hpp"
#include "input.hpp"

class Controller {
	private:
		View* view_;
		Model* model_;
		Input input_;
	public:
		Controller(View*, Model*);

		void handleInputs();
};