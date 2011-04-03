#include <SDL/SDL.h>
#include "tinyxml/tinyxml.h"

#include <string>
using std::string;

class IBaseEntity
{
public:
	virtual void		VThink	( const int& iElapsedTime )		= 0;
	virtual void		VRender( SDL_Surface* pDestSurface	)	= 0;

	virtual bool		VLoad	( TiXmlElement* pXMLData )		= 0;
	virtual TiXmlElement*	VGetSaveData	()				= 0;
};
