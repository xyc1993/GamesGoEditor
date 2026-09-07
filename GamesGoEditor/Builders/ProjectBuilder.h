#pragma once

#include <string>
#include <filesystem>

class ProjectBuilder
{
public:
	static void BuildProjectAt(const std::string& path, const std::string& projectName);
	static std::filesystem::path GetExecutableDirectory();
};
