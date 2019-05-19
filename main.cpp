//
// Created by arattel on 07.05.19.
//
#include <iostream>
#include <thread>
#include "decompress_list.h"
#include "input.h"
#include "count_words.h"
#include <vector>
#include "merge.h"
#include "config.h"
#include "conveyor.h"
#include "output.h"


template<class T, class F>
void print_map(std::map<T, F> my_map);

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


int main(int argc, char **argv) {
    std::string config_filename;

    if (argc > 1) {
        config_filename = argv[1];
    } else {
        config_filename = "config.dat";
    }

    //Getting config
    config config1 = read_config_from_file(config_filename);

    //Creating queues for conveyor
    StringQueue filenameQ;
    StringQueue textQ;
    MapQueue counted;
    int n_counting_thr = (int) config1.indexing_threads;
    int n_merging_thr = (int) config1.merging_threads;
    std::string out_by_a = config1.out_by_a;
    std::string out_by_n = config1.out_by_n;
    if (argc > 5) {
        n_counting_thr = std::stoi(argv[2]);
        n_merging_thr = std::stoi(argv[3]);
        out_by_a = argv[4];
        out_by_n = argv[5];
    }
    int counting_threads_left = n_counting_thr;
    std::thread counting_threads[n_counting_thr];
    std::thread merging_threads[n_merging_thr];
    std::mutex mutex;


    auto start = get_current_time_fenced();
    //Threads for conveyor
    std::thread directory_thread = std::thread(read_dir_convey, config1.infile, std::ref(filenameQ));
    std::thread read_thread = std::thread(read_files, std::ref(filenameQ), std::ref(textQ));


    for (int i = 0; i < n_counting_thr; i++) {
        counting_threads[i] = std::thread(count_words_in_texts, std::ref(textQ), std::ref(counted), std::ref(mutex),
                                          std::ref(counting_threads_left));
    }
    for (int i = 0; i < n_merging_thr; i++) {
        merging_threads[i] = std::thread(merge_all_maps, std::ref(counted));
    }

    directory_thread.join();
    read_thread.join();


    for (auto &counting_thread : counting_threads) {
        counting_thread.join();
    }
    for (auto &merging_thread: merging_threads) {
        merging_thread.join();
    }

    auto res = counted.pop();
    write_map_to_file(res, out_by_a);
    output_sorted_by_number(res, out_by_n);






    auto end = get_current_time_fenced();


    std::cout << "Total time:" << to_us(end - start) << std::endl;
    return 0;
}


template<class T, class F>
void print_map(std::map<T, F> my_map) {
    std::cout << "-----------------------------" << std::endl;
    for (auto elem : my_map) {
        std::cout << elem.first << " " << elem.second << "\n";
    }


}