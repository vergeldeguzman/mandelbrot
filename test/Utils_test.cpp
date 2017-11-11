/*
 * Utils_test.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: vergel
 */


#include "gtest/gtest.h"

#include "Utils.h"

using namespace std;

TEST(UtilsTest, GetFileSize) {
	EXPECT_EQ(11, utils::getFileSize("test/Resource/small_file"));
	EXPECT_EQ(0, utils::getFileSize("test/Resource/empty_file"));
}

TEST(UtilsTest, GetFileSizeInvalidArgument) {
	EXPECT_THROW(
		utils::getFileSize("test/Resource/invalid_file"),
		invalid_argument);
}

TEST(UtilsTest, Diff) {
	EXPECT_TRUE(
		utils::diff("test/Resource/small_file", "test/Resource/dup_small_file"));
	EXPECT_TRUE(
		utils::diff("test/Resource/10k_file", "test/Resource/dup_10k_file"));
	EXPECT_TRUE(
		utils::diff("test/Resource/10.5k_file1", "test/Resource/dup_10.5k_file1"));
	EXPECT_FALSE(
		utils::diff("test/Resource/10.5k_file1", "test/Resource/10.5k_file2"));
	EXPECT_FALSE(
		utils::diff("test/Resource/small_file", "test/Resource/empty_file"));
}

TEST(UtilsTest, DiffInvalidArugment) {
	EXPECT_THROW(
		utils::diff("test/Resource/invalid_file", "test/Resource/invalid_file"),
		invalid_argument);
}
