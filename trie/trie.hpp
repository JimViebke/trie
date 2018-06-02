#pragma once

#include <memory>
#include <vector>

namespace trie
{
	template<typename T, size_t branch_factor>
	class node
	{
	public:
		using node_type = node<T, branch_factor>;

		node() {}

		template <typename C> void insert(const C & c, size_t depth)
		{
			// if we have at least one more element to insert
			if (depth < c.size())
			{
				// if we have no children, create [branch_factor] children
				if (children.size() == 0)
				{
					fill();
				}

				children[c[depth]].insert(c, depth + 1);
			}
		}

		template <typename C> bool contains(const C & c, size_t depth)
		{
			if (depth < c.length())
			{
				if (children.empty())
				{
					return false;
				}

				return children[c[depth]].contains(c, depth + 1);
			}

			return !children.empty();
		}

	private:
		void fill()
		{
			children.reserve(branch_factor);
			for (size_t i = 0; i < branch_factor; ++i)
			{
				children.emplace_back();
			}
		}

		std::vector<node_type> children;
	};

	template <typename T, size_t branch_factor>
	class trie : public node<T, branch_factor>
	{
	public:
		template <typename C> void insert(const C & c)
		{
			((node<T, branch_factor>*)this)->insert(c, 0);
		}

		template <typename C> bool contains(const C & c)
		{
			return ((node<T, branch_factor>*)this)->contains(c, 0);
		}
	};
}
