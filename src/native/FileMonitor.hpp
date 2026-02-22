#pragma once

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <dispatch/queue.h>

#include "Memory.hpp"

namespace sst::fs {

class FileMonitor {
public:
  explicit FileMonitor(const char dirname[], dispatch_queue_t queue,
                       FSEventStreamCallback callback,
                       CFMutableArrayRef buffer);

  void start() const;

  CFStringRef directory() const noexcept { return directory_.get(); }

  CFMutableArrayRef buffer() noexcept { return buffer_; }

private:
  sst::mem::cf_ptr<CFStringRef> directory_;
  dispatch_queue_t queue_;
  sst::mem::cf_ptr<FSEventStreamRef> stream_{nullptr};
  CFMutableArrayRef buffer_;
};

} // namespace sst::fs
