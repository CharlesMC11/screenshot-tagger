#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <sysexits.h>

#include <iostream>

#include "img_utils.h"

char g_input_absolute_path[PATH_MAX];

struct DirectoryList {
  dirent** entries = nullptr;
  int count = 0;

  ~DirectoryList() {
    for (int i = 0; i < count; ++i) free(entries[i]);
    free(entries);
  }
};

int main(const int argc, const char* argv[]) {
  DirectoryList list;

  if (realpath((argc >= 2) ? argv[1] : ".", g_input_absolute_path) == NULL)
    return EX_NOINPUT;

  list.count =
      scandir(g_input_absolute_path, &list.entries, is_image, d_name_cmp);
  if (list.count <= 0) {
    std::cerr << "Error scanning directory\n";

    if (list.count == 0 || errno == ENOENT) return EX_NOINPUT;
    if (errno == EACCES) return EX_NOPERM;
    return EX_OSERR;
  }

  for (int i = 0; i < list.count; ++i)
    std::cout << g_input_absolute_path << '/' << list.entries[i]->d_name
              << '\n';

  return EX_OK;
}
