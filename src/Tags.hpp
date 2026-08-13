#pragma once

#include <Geode/Geode.hpp>
#include <string_view>
#include <algorithm>

using namespace geode::prelude;
class Tags {
public:
    static inline std::vector<std::string_view> modData = {
        "gd"
    };
    static void addTag(std::string_view name) {
        const auto slash = name.find('/');

        if (slash != std::string_view::npos) {
            const auto tag = name.substr(0, slash);

            if (std::ranges::find(modData, tag) == modData.end()) {
                modData.emplace_back(tag);
            }
        }
    }
};

#define __CONCAT_DETAIL(x, y) x##y
#define __CONCAT(x, y) __CONCAT_DETAIL(x, y)

#define ADD_TAG(name, ...) \
namespace { \
    struct __CONCAT(AutoRegisterTag, __LINE__) { \
        __CONCAT(AutoRegisterTag, __LINE__)() { \
            Tags::addTag(name); \
        } \
    } __CONCAT(autoRegisterTag, __LINE__); \
} \
static_assert(true, "")

