#include "Sorter.hpp"

#include <CoreFoundation/CoreFoundation.h>

#include <iostream>

namespace sst::sorter {

void naturalSort(CFMutableArrayRef list) {
  CFArraySortValues(
      list, CFRangeMake(0, CFArrayGetCount(list)),
      [](const void *a, const void *b, void *) {
        const auto u1{static_cast<CFURLRef>(a)};
        const auto u2{static_cast<CFURLRef>(b)};

        return CFStringCompare(CFURLGetString(u1), CFURLGetString(u2),
                               kCFCompareCaseInsensitive |
                                   kCFCompareDiacriticInsensitive |
                                   kCFCompareLocalized | kCFCompareNumerically);
      },
      nullptr);
}

void printSorted(CFMutableArrayRef list) {
  const CFIndex count{CFArrayGetCount(list)};
  if (!list || count == 0)
    return;

  naturalSort(list);

  std::cout << "[sstd] Printing buffer contents:\n";
  for (CFIndex i{0}; i < count; ++i) {
    const auto url{static_cast<CFURLRef>(CFArrayGetValueAtIndex(list, i))};

    char path[PATH_MAX];
    if (CFURLGetFileSystemRepresentation(
            url, true, reinterpret_cast<UInt8 *>(path), PATH_MAX))
      std::cout << path << '\n';
  }
  std::cout << std::flush;
}

} // namespace sst::sorter
