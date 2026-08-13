
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>

#include <macros.hpp>

namespace fs = std::filesystem;

struct SourceTag {
	std::string name;
	std::string file;
	std::size_t line;
};

std::vector<SourceTag> getSourceTags() {
	std::vector<SourceTag> tags;

	if (!fs::exists(SOURCE_DIRECTORY)) {
		return tags;
	}

	for (const auto &entry :
	     fs::recursive_directory_iterator(SOURCE_DIRECTORY)) {

		if (!entry.is_regular_file()) {
			continue;
		}

		const auto extension = entry.path().extension();

		if (extension != ".cpp" &&
		    extension != ".hpp" &&
		    extension != ".h") {
			continue;
		}

		std::ifstream file(entry.path());

		if (!file) {
			continue;
		}

		std::string line;
		std::size_t lineNumber = 0;

		while (std::getline(file, line)) {
			++lineNumber;

			std::smatch match;

			auto begin = line.cbegin();
			auto end = line.cend();

			while (std::regex_search(
			    begin,
			    end,
			    match,
			    commentPattern)) {
				tags.push_back({match[1].str(),
				                entry.path().generic_string(),
				                lineNumber});

				begin = match.suffix().first;
			}

			begin = line.cbegin();

			while (std::regex_search(
			    begin,
			    end,
			    match,
			    macroPattern)) {
				tags.push_back({match[1].str(),
				                entry.path().generic_string(),
				                lineNumber});

				begin = match.suffix().first;
			}
		}
	}

	return tags;
}

std::set<std::string> getPreviewTags(
    const fs::path &directory) {
	std::set<std::string> tags;

	if (!fs::exists(directory)) {
		return tags;
	}

	for (const auto &entry :
	     fs::directory_iterator(directory)) {

		if (!entry.is_regular_file()) {
			continue;
		}

		if (entry.path().extension() != ".png") {
			continue;
		}

		std::string name = entry.path().stem().string();

		if (name.size() >= 7 &&
		    name.ends_with("Preview")) {
			name.erase(name.size() - 7);
		}

		tags.insert(name);
	}

	return tags;
}

std::vector<std::string> getMisformattedFiles(
    const fs::path &directory) {
	std::vector<std::string> files;

	if (!fs::exists(directory)) {
		return files;
	}

	for (const auto &entry :
	     fs::directory_iterator(directory)) {

		if (!entry.is_regular_file()) {
			continue;
		}

		if (entry.path().extension() != ".png") {
			continue;
		}

		const std::string name =
		    entry.path().stem().string();

		if (name.size() < 7 ||
		    !name.ends_with("Preview")) {
			files.push_back(
			    entry.path().filename().string());
		}
	}

	std::sort(files.begin(), files.end());

	return files;
}

void printMissingWarnings(
    const std::vector<SourceTag> &sourceTags,
    const std::set<std::string> &previewTags,
    const std::string &previewName) {
	std::set<std::string> reported;

	for (const auto &tag : sourceTags) {
		if (previewTags.contains(tag.name)) {
			continue;
		}

		if (reported.contains(tag.name)) {
			continue;
		}

		reported.insert(tag.name);

		std::cerr
		    << tag.file
		    << ":"
		    << tag.line
		    << ":1: warning: Missing "
		    << previewName
		    << " preview for tag '"
		    << tag.name
		    << "'\n";
	}
}

void printMisformattedWarnings(
    const std::vector<std::string> &files,
    const std::string &previewName) {
	for (const auto &file : files) {
		std::cerr
		    << previewName
		    << ": warning: Misformatted preview filename '"
		    << file
		    << "'\n";
	}
}

int main() {
	try {
		const auto sourceTags = getSourceTags();

		const auto swelvyTags =
		    getPreviewTags(PREVIEWS_DIRECTORY);

		const auto sapphireTags =
		    getPreviewTags(SAPPHIRE_DIRECTORY);

		const auto badSwelvy =
		    getMisformattedFiles(PREVIEWS_DIRECTORY);

		const auto badSapphire =
		    getMisformattedFiles(SAPPHIRE_DIRECTORY);

		printMissingWarnings(
		    sourceTags,
		    swelvyTags,
		    "SwelvyBG");

		printMissingWarnings(
		    sourceTags,
		    sapphireTags,
		    "Sapphire");

		printMisformattedWarnings(
		    badSwelvy,
		    "SwelvyBG");

		printMisformattedWarnings(
		    badSapphire,
		    "Sapphire");

		return 0;
	}

	catch (const fs::filesystem_error &error) {
		std::cerr
		    << error.what()
		    << '\n';

		return 1;
	}

	catch (const std::exception &error) {
		std::cerr
		    << error.what()
		    << '\n';

		return 1;
	}
}
