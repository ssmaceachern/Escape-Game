#include "Object.h"
#include "EventStep.h"

#include <iomanip>
#include <locale>
#include <sstream>

using std::string;
using std::ostringstream;

class Points : public Object{

	protected:
		int stepCounter;
		int doubleCounter;
		int score;
		void step();
		string NumberToString(int n);
		
	public:
		Points();
		int eventHandler(Event *p_e);
		void draw();

};
