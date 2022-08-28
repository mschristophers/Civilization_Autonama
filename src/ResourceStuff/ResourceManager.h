// #pragma once

#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <string>
#include <unordered_map>

template <typename Resource>

class ResourceManager {
	using CrString = const std::string&;

public:
	ResourceManager(CrString folder, CrString extension)
		: civ_folder("res/" + folder + "/")
		, civ_extension("." + extension)
	{
	}

	const Resource& get(CrString name)
	{
		if (!exists(name)) {
			add(name);
		}

		return civ_resources.at(name);
	}

	bool exists(CrString name) const
	{
		return civ_resources.find(name) != civ_resources.end();
	}

	void add(CrString name)
	{
		Resource res;

		// If the resource fails to load, it adds a default "fail" resource
		if (!res.loadFromFile(getFullName(name))) {
			Resource fail;
			fail.loadFromFile(civ_folder + "_fail_" + civ_extension);
			civ_resources.insert(std::make_pair(name, fail));
		}
		else {
			civ_resources.insert(std::make_pair(name, res));
		}
	}

private:
	std : string getFullName(CrString name)
	{
		return civ_folder + name + civ_extension;
	}

	const std::string civ_folder;
	const std::string civ_extension;

	std::unordered_map<std::string, Resource> civ_resources;
};

#endif // For RESOURCEMANAGER_H_INCLUDED