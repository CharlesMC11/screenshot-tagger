#pragma once

#include <stdint.h>

#ifdef __cplusplus
namespace sst::signatures {
extern "C" {
#endif

uint32_t is_image(uint8_t buffer[]);

#ifdef __cplusplus
}  // extern "C"
}  // namespace sst::signatures
#endif
