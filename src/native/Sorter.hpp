#pragma once

#include <CoreFoundation/CFArray.h>

namespace sst::sorter {

void naturalSort(CFMutableArrayRef list);

void printSorted(CFMutableArrayRef list);

} // namespace sst::sorter
