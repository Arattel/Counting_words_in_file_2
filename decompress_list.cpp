//
// Created by arattel on 29.04.19.
//
#include "decompress_list.h"


void read_directory(const std::string &name, StringQueue &q) {
    std::vector<std::string> v;
    boost::filesystem::path p(name);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    for (start; start != end; ++start) {
        //Якщо це звичайний файл
        if (boost::filesystem::is_regular(start->path()) && is_zip(start->path().string())) {
            std::string pth = get_filename_path_without_extension(start->path().string());
            extract(start->path().string().c_str(), pth);
        } else if (boost::filesystem::is_regular(start->path()) && is_txt(start->path().string())) {
            q.push(start->path().string());
        }
            //Якщо це директорія
        else if (boost::filesystem::is_directory(start->path())) {
            read_directory(start->path().string(), q);
        }
    }
}
void read_dir_convey(const std::string &name, StringQueue &q){
    read_directory(name, q);
    q.push("Dead");
}
bool is_zip(std::string filename) {
    return filename.substr(filename.find_last_of(".") + 1) == "zip" ||filename.substr(filename.find_last_of(".") + 1) == "ZIP" ;
}
//


std::string get_filename_path_without_extension(std::string filename) {
    return filename.substr(0, filename.find_last_of(".")) + "/";
}

bool is_txt(std::string filename){
    return filename.substr(filename.find_last_of(".") + 1) == "txt" ||filename.substr(filename.find_last_of(".") + 1) == "TXT" ;
}

//std::vector<std::string> extract_and_get_list(std::string archive_path, std::string destination) {
//    extract(archive_path.c_str(), destination);
//    return get_list(destination);
//}
//
//std::vector<std::string> get_list(std::string directory){
//    std::vector<std::string> result;
//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir (directory.c_str())) != NULL) {
//        /* print all the files and directories within directory */
//        while ((ent = readdir (dir)) != NULL) {
//            result.push_back(ent->d_name);
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return std::vector<std::string>();;
//    }
//    return result;
//}
//


