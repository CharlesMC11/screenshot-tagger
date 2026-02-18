#include "Scanner.hpp"

#include <dirent.h>
#include <fcntl.h>
#include <sysexits.h>
#include <unistd.h>

#include <cstdint>

#include "Signatures.h"

namespace sst::scanner {

uint32_t collect_images(const char* dirname, std::vector<std::string>& list) {
  int dfd{open(dirname, O_RDONLY | O_DIRECTORY)};
  if (dfd < 0) return EX_NOINPUT;

  DIR* dirp{fdopendir(dfd)};
  if (dirp == nullptr) {
    close(dfd);
    return EX_NOINPUT;
  }

  dirent* entry;
  while ((entry = readdir(dirp)) != nullptr) {
    if (entry->d_type != DT_REG) continue;

    int fd{openat(dfd, entry->d_name, O_RDONLY | O_CLOEXEC)};
    if (fd < 0) continue;

    fcntl(fd, F_NOCACHE, 1);

    alignas(16) uint8_t buffer[16];
    if (read(fd, buffer, sizeof(buffer)) < 12) {
      close(fd);
      continue;
    }

    if (sst::signatures::is_image(buffer)) {
      list.emplace_back(entry->d_name);
    }
    close(fd);
  }
  closedir(dirp);

  return EX_OK;
}

}  // namespace sst::scanner
