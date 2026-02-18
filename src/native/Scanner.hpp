#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace sst::scanner {

uint32_t collect_images(const char* dirname, std::vector<std::string>& list);

}  // namespace sst::scanner
