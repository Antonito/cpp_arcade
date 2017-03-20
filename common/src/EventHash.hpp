#include <cstdlib>
#include "Event.hpp"

namespace arcade
{
	template <typename T>
	class EventHash;

	template <>
	class EventHash<Event>
	{
	public:
		std::size_t operator()(Event const &e) const
		{
			if (e.type == EventType::ET_NONE || e.type == EventType::ET_QUIT)
			{
				return (e.type);
			}
			return (e.type ^ (e.action << 8) ^ (e.kb_key << 16));
		}
	};
}