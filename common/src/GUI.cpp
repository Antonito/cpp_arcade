#include "GUI.hpp"

namespace arcade
{
	GUI::GUI()
	{}

	GUI::~GUI()
	{}

	std::size_t GUI::size() const
	{
		return (m_components.size());
	}

	Component & GUI::at(std::size_t n)
	{
		return (m_components[n]);
	}

	Component const & GUI::at(std::size_t n) const
	{
		return (m_components[n]);
	}

	void GUI::push(Component const & component)
	{
		m_components.push_back(component);
	}

	void GUI::push(Component && component)
	{
		m_components.push_back(component);
	}

	void GUI::insert(Component const & component, std::size_t pos)
	{
		m_components.insert(m_components.begin() + pos, component);
	}

	void GUI::insert(Component && component, std::size_t pos)
	{
		m_components.insert(m_components.begin() + pos, component);
	}

	void GUI::erase(std::size_t pos)
	{
		m_components.erase(m_components.begin() + pos);
	}

	void GUI::erase(std::size_t pos, std::size_t size)
	{
		m_components.erase(m_components.begin() + pos, m_components.begin() + pos + size);
	}

	void GUI::clear()
	{
		m_components.clear();
	}
}