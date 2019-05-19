from helpers import call_and_get_result, files_equal


def test_time(config, counting, merging, interations):
    all_same = True
    test_times = []
    etalon_files = ["etalon{}{}a.txt".format(counting, merging), "etalon{}{}n.txt".format(counting, merging)]
    test_files = ["test{}{}a.txt".format(counting, merging), "test{}{}n.txt".format(counting, merging)]
    time = call_and_get_result(
        ["./Counting_words_in_file", config, str(counting), str(merging), etalon_files[0], etalon_files[1]])
    print(time)

    test_times.append(time)
    for i in range(interations - 1):
        time = call_and_get_result(
            ["./Counting_words_in_file", config, str(counting), str(merging), test_files[0], test_files[1]])
        print(time)
        try:
            if not (files_equal(etalon_files[0], test_files[0]) and files_equal(etalon_files[1], test_files[1])):
                all_same = False
        except Exception:
            pass
        test_times.append(time)

    test_times = list(map(lambda x: x['Total time'], test_times))
    best_time = min(test_times)
    return {'Counting': counting, 'Merging': merging, 'Best time': best_time, 'All same': all_same}


all_times = []
for i in range(1, 5):
    for j in range(1, 5):
        all_times.append(test_time("config.txt", i, j, 5))

with open("result.txt", 'w') as file:
    file.write('counting,merging,best_time')
    for i in all_times:
        file.write('{},{},{}\n'.format(i['Counting'], i['Merging'], i['Best time']))
