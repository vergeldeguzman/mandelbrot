/*
 * Utils.h
 *
 *  Created on: Nov 10, 2017
 *      Author: vergel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>

namespace utils {

/**
 * Get the file size in bytes
 */
int getFileSize(const std::string& filename);

/**
 * Compare two files and return true if contents are the same,
 * otherwise false
 */
bool diff(const std::string& file1, const std::string& file2);

/**
 * Split string by delimiter to vector
 */
std::vector<std::string> splitString(const std::string& input, char delimiter);

} // namespace utils

#endif /* UTILS_H_ */
