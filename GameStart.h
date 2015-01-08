#include "Object.h"
#include "WallManager.h"
#include "ObjectFactory.h"

#define ln1 "    ___       ___       ___       ___       ___       ___   "
#define ln2 "   /\\  \\     /\\  \\     /\\  \\     /\\  \\     /\\  \\     /\\  \\  "
#define ln3 "  /::\\  \\   /::\\  \\   /::\\  \\   /::\\  \\   /::\\  \\   /::\\  \\ "
#define ln4 " /::\\:\\__\\ /\\:\\:\\__\\ /:/\\:\\__\\ /::\\:\\__\\ /::\\:\\__\\ /::\\:\\__\\"
#define ln5 " \\:\\:\\/  / \\:\\:\\/__/ \\:\\ \\/__/ \\/\\::/  / \\/\\::/  / \\:\\:\\/  /"
#define ln6 "  \\:\\/  /   \\::/  /   \\:\\__\\     /:/  /     \\/__/   \\:\\/  / "
#define ln7 "   \\/__/     \\/__/     \\/__/     \\/__/               \\/__/  "

using std::string;

class GameStart : public Object {
	protected:
		void step();
		void start();
		bool gameStart;
		WallManager* wall_manager;
		ObjectFactory* obj_factory;
		
	public:
		GameStart();
		int eventHandler(Event *p_e);
		void draw();
};
