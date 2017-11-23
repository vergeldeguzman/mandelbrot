/*
 * Utils.cpp

 *
 *  Created on: Nov 10, 2017
 *      Author: vergel
 */

#include "Utils.h"

#include <sys/stat.h>
#include <cstring>
#include <exception>
#include <fstream>

using namespace std;

namespace utils {

int getFileSize(const string& filename) {

	struct stat64 buf;
	int fileStatus = stat64(filename.c_str(), &buf);
	if (fileStatus != 0) {
		throw invalid_argument("Cannot get file size of " + filename);
	}
	return buf.st_size;
}

bool diff(const string& file1, const string& file2) {
	const int FILE_BUFFER_SIZE = 10240;

	int fileSize1 = utils::getFileSize(file1);
	int fileSize2 = utils::getFileSize(file2);

	if (fileSize1 != fileSize2) {
		return false;
	}

	ifstream ifs1;
	ifs1.open(file1, ios::binary);
	if (!ifs1) {
		throw invalid_argument("Cannot open " + file1);
	}

	ifstream ifs2;
	ifs2.open(file2, ios::binary);
	if (!ifs2) {
		throw invalid_argument("Cannot open " + file2);
	}

	bool status = false;
	char buf1[FILE_BUFFER_SIZE];
	char buf2[FILE_BUFFER_SIZE];
	while (ifs1 && ifs2) {
		ifs1.read(buf1, sizeof(buf1));
		int bytesRead1 = ifs1.gcount();

		ifs2.read(buf2, sizeof(buf2));
		int bytesRead2 = ifs2.gcount();

		if (bytesRead1 != bytesRead2) {
			status = false;
			break;
		}

		if (strncmp(buf1, buf2, bytesRead1) != 0) {
			status = false;
			break;
		}

		status = true;
	}

	ifs1.close();
	ifs2.close();
	return status;
}

vector<string> splitString(const string& input, char delimiter) {
	vector<string> strings;

	size_t idx = 0;
	size_t found = 0;
	auto len = input.size();
	while (idx < len && (found = input.find(delimiter, idx)) != string::npos) {
		strings.push_back(input.substr(idx, found - idx));
		idx = found + 1;
	}

	if (idx < len) {
		strings.push_back(input.substr(idx, found - idx));
	}
	// add empty if last char is a delimeter
	if (len > 0 && input[len - 1] == delimiter) {
		strings.push_back("");
	}

	return strings;
}

} // namespace utils

