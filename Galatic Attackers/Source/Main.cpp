// handles everything
#include "Application.h"
// program entry point
int main()
{
	Application galacticAttackers;
	if (galacticAttackers.Init()) {
		if (galacticAttackers.Run()) {
			return galacticAttackers.Shutdown() ? 0 : 1;
		}
		
	}
	return 1;
}