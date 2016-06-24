#pragma once

struct Entity
{
	std::string oldname;
	std::string newname;
	inline
	friend bool operator <(const Entity& x, const Entity& y) //operator overload for sorting 
	{
		return x.oldname < y.oldname;
	}
};