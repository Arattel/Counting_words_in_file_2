//
// Created by arattel on 12.05.19.
//

#ifndef COUNTING_WORDS_IN_FILE_CONVEYOR_H
#define COUNTING_WORDS_IN_FILE_CONVEYOR_H

#include "thr_safe_queue.h"
#include "input.h"


void read_files(StringQueue &q, StringQueue &out);

void count_words_in_texts(StringQueue &q, MapQueue &out, std::mutex &mutex, int &threads_left);

void merge_all_maps(MapQueue &maps);

#endif //COUNTING_WORDS_IN_FILE_CONVEYOR_H
