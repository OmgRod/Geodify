#include <filesystem>
#include <fstream>
#include <iostream>
#include <macros.hpp>
#include <nlohmann/json.hpp>
#include <regex>
#include <string>


namespace fs = std::filesystem;
using json = nlohmann::ordered_json;


#define MERGE_JSON "geodeify.json"
#define OUTPUT_JSON "mod.json"


std::string replaceUnderscores(std::string value) {
    for (char& character : value) {
        if (character == '_') {
            character = ' ';
        }
    }

    return value;
}


int main() {
    try {
        std::cout << "Creating mod.json for geode!\n";

        json tagSettings = json::object();


        if (!fs::exists(SOURCE_DIRECTORY)) {
            std::cerr
                << "Error: Mod's code folder doesn't exist? "
                << SOURCE_DIRECTORY
                << '\n';

            return 1;
        }


        for (const auto& entry :
             fs::recursive_directory_iterator(SOURCE_DIRECTORY)) {

            if (!entry.is_regular_file()) {
                continue;
            }

            if (entry.path().extension() != ".cpp") {
                continue;
            }


            std::ifstream file(entry.path());

            if (!file) {
                std::cerr
                    << "Warning: failed to open "
                    << entry.path().string()
                    << '\n';

                continue;
            }


            std::string line;

            while (std::getline(file, line)) {
                std::smatch match;


                bool found = std::regex_search(
                    line,
                    match,
                    commentPattern
                );


                if (!found) {
                    found = std::regex_search(
                        line,
                        match,
                        macroPattern
                    );
                }


                if (!found) {
                    continue;
                }

                const std::string name = match[1].str();
                std::string TrueName = "";

                std::string afterLast;


                if (
                    match.size() > 2 &&
                    match[2].matched &&
                    !match[2].str().empty()
                ) {
                    TrueName = match[2].str();
                }

                {
                    const std::size_t separator = name.rfind('/');

                    if (separator == std::string::npos) {
                        afterLast = name;
                    }
                    else {
                        afterLast = name.substr(separator + 1);
                    }
                    if (TrueName.empty()) {
                        TrueName = afterLast;
                    };
                }


                if (tagSettings.contains(name)) {
                    continue;
                }


                tagSettings[name] = {
                    {
                        "name",
                        replaceUnderscores(TrueName)
                    },
                    {
                        "description",
                        afterLast
                    },
                    {
                        "type",
                        "bool"
                    },
                    {
                        "default",
                        false
                    }
                };


                std::cout
                    << "Found tag: "
                    << name
                    << " with name "
                    << TrueName
                    << "description" << afterLast
                    << '\n';
            }
        }


        json modData = json::object();


        if (fs::exists(MERGE_JSON)) {
            std::ifstream input(MERGE_JSON);

            if (!input) {
                std::cerr
                    << "Error: failed to open "
                    << MERGE_JSON
                    << '\n';

                return 1;
            }


            try {
                input >> modData;
            }
            catch (const json::parse_error& error) {
                std::cerr
                    << "Error: failed to parse "
                    << MERGE_JSON
                    << ":\n"
                    << error.what()
                    << '\n';

                return 1;
            }
        }


        json existingSettings = json::object();


        if (
            modData.contains("settings") &&
            modData["settings"].is_object()
        ) {
            existingSettings = modData["settings"];
        }


        json mergedSettings = json::object();

        bool inserted = false;


        for (auto& [key, value] : existingSettings.items()) {

            if (key == "other-title" && !inserted) {

                for (auto& [newKey, newValue] : tagSettings.items()) {
                    if (!existingSettings.contains(newKey)) {
                        mergedSettings[newKey] = newValue;
                    }
                }

                inserted = true;
            }


            mergedSettings[key] = value;
        }


        if (!inserted) {
            for (auto& [newKey, newValue] : tagSettings.items()) {
                if (!existingSettings.contains(newKey)) {
                    mergedSettings[newKey] = newValue;
                }
            }
        }


        json outputData = json::object();


        for (auto& [key, value] : modData.items()) {

            if (key == "settings") {
                outputData[key] = std::move(mergedSettings);
            }
            else {
                outputData[key] = value;
            }
        }


        if (!modData.contains("settings")) {
            outputData["settings"] = std::move(mergedSettings);
        }


        std::ofstream output(OUTPUT_JSON);


        if (!output) {
            std::cerr
                << "Error: failed to create "
                << OUTPUT_JSON
                << '\n';

            return 1;
        }


        output << outputData.dump(4) << '\n';


        std::cout
            << "Processed "
            << tagSettings.size()
            << " tags and generated "
            << OUTPUT_JSON
            << '\n';


        return 0;
    }


    catch (const fs::filesystem_error& error) {
        std::cerr
            << "Filesystem error: "
            << error.what()
            << '\n';

        return 1;
    }


    catch (const json::exception& error) {
        std::cerr
            << "JSON error: "
            << error.what()
            << '\n';

        return 1;
    }


    catch (const std::exception& error) {
        std::cerr
            << "Error: "
            << error.what()
            << '\n';

        return 1;
    }
}
