#include "ProjectBuilder.h"

#include <Windows.h>

void ProjectBuilder::BuildProjectAt(const std::string& path, const std::string& projectName)
{
	std::string projectPathString = path + "/" + projectName;
	std::filesystem::path projectPath(projectPathString);
	std::filesystem::create_directories(projectPath);

	std::string projectSourcePathString = projectPathString + "/Source";
	std::filesystem::path projectSourcePath(projectSourcePathString);
	std::filesystem::create_directories(projectSourcePath);

	auto currentPath = GetExecutableDirectory();
	auto includePath = currentPath / "Include";
	auto templatePath = currentPath / "ProjectTemplateFiles";
	auto templateSourcePath = templatePath / "Source";

	std::filesystem::copy_file(templateSourcePath / "Game.cpp", projectSourcePath / "Game.cpp", std::filesystem::copy_options::overwrite_existing);

	std::string cMakeCommand =
		"cmake -S \"" + templatePath.string() +
		"\" -B \"" + (projectPath / "Build").string() + "\"" +
		" -DPROJECT_NAME=\"" + projectName + "\"" +
		" -DENGINE_INCLUDE_DIR=" + "\"" + includePath.string() + "\"" +
		" -DENGINE_LIBRARY_DIR=" + "\"" + currentPath.string() + "\"";

	int result = std::system(cMakeCommand.c_str());	
	if (result != 0)
	{
		printf("CMake generation failed\n");
	}
}

// Windows only implementation
std::filesystem::path ProjectBuilder::GetExecutableDirectory()
{
	wchar_t buffer[MAX_PATH];

	DWORD length = GetModuleFileNameW(
		nullptr,
		buffer,
		MAX_PATH
	);

	if (length == 0)
	{
		throw std::runtime_error("Failed to get executable path");
	}

	return std::filesystem::path(buffer).parent_path();
}
