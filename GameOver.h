#define gln1 "    ___      ___      ___      ___           ___      ___      ___      ___   "
#define gln2 "   /\\  \\    /\\  \\    /\\__\\    /\\  \\         /\\  \\    /\\__\\    /\\  \\    /\\  \\  "
#define gln3 "  /::\\  \\  /::\\  \\  /::L_L_  /::\\  \\       /::\\  \\  /:/ _/_  /::\\  \\  /::\\  \\ "
#define gln4 " /:/\\:\\__\\/::\\:\\__\\/:/L:\\__\\/::\\:\\__\\     /:/\\:\\__\\|::L/\\__\\/::\\:\\__\\/::\\:\\__\\"
#define gln5 " \\:\\:\\/__/\\/\\::/  /\\/_/:/  /\\:\\:\\/  /     \\:\\/:/  /|::::/  /\\:\\:\\/  /\\;:::/  /"
#define gln6 "  \\::/  /   /:/  /   /:/  /  \\:\\/  /       \\::/  /  L;;/__/  \\:\\/  /  |:\\/__/ "
#define gln7 "   \\/__/    \\/__/    \\/__/    \\/__/         \\/__/             \\/__/    \\|__|  "

#include "Object.h"
#include "EventStep.h"

class GameOver : public Object {
	protected:
		void step();
		int time_to_live;

	public:
		GameOver();
		~GameOver();
		int eventHandler(Event *p_e);
		void draw();
};
