#include "FileMonitor.hpp"

#include <CoreServices/CoreServices.h>
#include <dispatch/queue.h>

#include "Inspector.hpp"
#include "Memory.hpp"

namespace sst::fs {

FileMonitor::FileMonitor(const char dirname[], dispatch_queue_t queue,
                         FSEventStreamCallback callback,
                         CFMutableArrayRef buffer)
    : directory_{CFStringCreateWithCString(nullptr, dirname,
                                           kCFStringEncodingUTF8)},
      queue_{queue}, buffer_{buffer} {
  FSEventStreamContext context = {0, static_cast<void *>(this), nullptr,
                                  nullptr, nullptr};

  sst::mem::cf_ptr<CFArrayRef> paths{
      CFArrayCreate(nullptr, reinterpret_cast<const void **>(&directory_), 1,
                    &kCFTypeArrayCallBacks)};

  stream_.reset(FSEventStreamCreate(nullptr, callback, &context, paths.get(),
                                    kFSEventStreamEventIdSinceNow, 0.1,
                                    kFSEventStreamCreateFlagFileEvents |
                                        kFSEventStreamCreateFlagNoDefer));
}

void FileMonitor::start() const {
  if (stream_) {
    FSEventStreamSetDispatchQueue(stream_.get(), queue_);
    FSEventStreamStart(stream_.get());
  }
}

} // namespace sst::fs
