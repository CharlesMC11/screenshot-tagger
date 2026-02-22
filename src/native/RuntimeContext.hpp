#pragma once

#include "FileMonitor.hpp"

namespace sst::rt {

struct RuntimeContext {
  const fs::FileMonitor &watcher;
  const CFMutableArrayRef buffer;
  const dispatch_queue_t queue;
};

} // namespace sst::rt
