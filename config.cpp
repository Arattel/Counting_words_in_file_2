//
// Created by arattel on 28.04.19.
//
#include "config.h"


config read_config_from_file(std::string filename) {
    std::ifstream infile(filename);
    std::vector<std::string> values;
    if (infile.is_open()) {
        std::string line;
        while (getline(infile, line)) {
            values.push_back(get_config_value(line));
        }
    }
    config conf;
    conf.infile = values[0];
    conf.out_by_a = values[1];
    conf.out_by_n = values[2];
    conf.indexing_threads = (size_t) std::stoi(values[3]);
    conf.merging_threads = (size_t) std::stoi(values[4]);
    return conf;
}


std::string get_config_value(std::string line) {
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    auto delimiterPos = line.find("=");
    line =  line.substr(delimiterPos + 1);
    line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
    return line;
}





