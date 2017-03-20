#include "Event.hpp"

namespace arcade
{
	bool Event::operator==(Event const & e) const
	{
		if (this->type == ET_NONE || this->type == ET_QUIT)
		{
			return (this->type == e.type);
		}
		else
		{
			return (this->type == e.type && this->action == e.action &&
				this->kb_key == e.kb_key);
		}
	}
}