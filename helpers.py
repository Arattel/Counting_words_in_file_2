import subprocess


def files_equal(file1, file2):
    """
    (str, str) -> (bool)
    """
    file1 = open(file1, 'r')
    file2 = open(file2, 'r')
    file1 = file1.readlines()
    file2 = file2.readlines()
    if len(file1) != len(file2):
        return False
    else:
        for i in range(len(file1)):
            if file1[i] != file2[i]:
                return False
        return True


def call_and_get_result(console_args):
    """
    (list) -> (list)
    Calls c++ script and gets its output
    """
    process = subprocess.Popen(console_args, stdout=subprocess.PIPE)
    results = {}
    for line in process.stdout:
        res = str(line).split("'")[1].split('\\n')[0].strip().split(":")
        res = list(map(lambda x: x.strip(), res))
        results[res[0]] = int(res[1])
    return results
