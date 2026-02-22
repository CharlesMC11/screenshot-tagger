#pragma once

#include "RuntimeContext.hpp"

namespace sst::rt {

void registerSignalHandler(int signal, RuntimeContext state);

}
