//
// Created by arattel on 12.05.19.
//
#include "conveyor.h"
#include "merge.h"
#include "count_words.h"


void read_files(StringQueue &q, StringQueue &out) {
    std::string res = q.pop();

    while (res != "") {
        out.push(format(read(res)));
        res = q.pop();
    }
    out.push("Dead");
}


void count_words_in_texts(StringQueue &q, MapQueue &out, std::mutex &mutex, int &threads_left) {
    std::string text = q.pop();
    while (!text.empty()) {
        out.push(count_words(get_words(text)));
        text = q.pop();
    }
    mutex.lock();
    if (threads_left == 1) {
        std::map<std::string, int> empty_map = std::map<std::string, int>();
        out.push(empty_map);
    } else {
        threads_left--;
    }
    mutex.unlock();
}


void merge_all_maps(MapQueue &maps) {
    std::vector <std::map<std::string, int>> maps_to_merge = maps.double_pop();
    while (!maps_to_merge[1].empty()) {
        std::map<std::string, int> merged = merge_two_maps(maps_to_merge[0], maps_to_merge[1]);
        maps.push(merged);
        maps_to_merge = maps.double_pop();
    }
}
