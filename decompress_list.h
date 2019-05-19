//
// Created by arattel on 29.04.19.
//

#ifndef COUNTING_WORDS_IN_FILE_DECOMPRESS_LIST_H
#define COUNTING_WORDS_IN_FILE_DECOMPRESS_LIST_H

#include "unzip.h"
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include "thr_safe_queue.h"


struct path_leaf_string {
    std::string operator()(const boost::filesystem::directory_entry &entry) const {
        return entry.path().leaf().string();
    }
};


void read_directory(const std::string &name, StringQueue &q);

void read_dir_convey(const std::string &name, StringQueue &q);

bool is_zip(std::string filename);

std::string get_filename_path_without_extension(std::string filename);

bool is_txt(std::string filename);
//std::vector<std::string> get_list(std::string directory);

//std::vector<std::string> extract_and_get_list(std::string archive_path, std::string destination);

#endif //COUNTING_WORDS_IN_FILE_DECOMPRESS_LIST_H
