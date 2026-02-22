#pragma once

#include <CoreFoundation/CFArray.h>
#include <CoreServices/CoreServices.h>

#include <cstdint>

namespace sst::inspector {

void scanDirectory(const char dirname[], CFMutableArrayRef buffer);

void scanDirectory(ConstFSEventStreamRef streamRef, void *clientCallbackInfo,
                   size_t numEvents, void *eventPaths,
                   const FSEventStreamEventFlags eventFlags[],
                   const FSEventStreamEventId eventIds[]);

} // namespace sst::inspector
