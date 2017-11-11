/*
 * utils.h
 *
 *  Created on: Nov 10, 2017
 *      Author: vergel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace utils {

int getFileSize(const std::string& filename);
bool diff(const std::string& file1, const std::string& file2);

} // namespace utils

#endif /* UTILS_H_ */
