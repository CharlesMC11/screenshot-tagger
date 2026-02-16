#pragma once
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

int is_image(const dirent*);

/*!
 * Compare the names of two directory entries, ensuring `name 1.ext` comes
 * after `name.ext`.
 *
 * @param d1
 * An address of a directory entry
 *
 * @param d2
 * An address of a directory entry
 *
 * @result
 * `-1` if `d1` is lexigraphically less than `d2`; `0` if they are the same;
 * `1` if `d1` is lexigraphically greater than `d2`
 */
int d_name_cmp(const dirent** d1, const dirent** d2);

#ifdef __cplusplus
}
#endif
