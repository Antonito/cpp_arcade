#ifndef GUI_HPP_
#define GUI_HPP_

#include <vector>
#include "IGUI.hpp"
#include "Component.hpp"

namespace arcade
{
	class GUI : public IGUI
	{
	public:
		GUI();
		GUI(GUI const &other) = delete;
		virtual ~GUI();

		GUI &operator=(GUI const &other) = delete;

		virtual std::size_t size() const;

		virtual IComponent &at(std::size_t n);
		virtual IComponent const &at(std::size_t n) const;

		void push(Component const &component);
		void push(Component &&component);

		void insert(Component const &component, std::size_t pos);
		void insert(Component &&component, std::size_t pos);

		void erase(std::size_t pos);
		void erase(std::size_t pos, std::size_t size);

		void clear();

	private:
		std::vector<Component> m_components;
	};
}

#endif // !GUI_HPP_