"""
This Code converts all files in #includes that are relative to /src so that they are
instead relative to the file with said #include in.

This is necessary so code compiles in arduino IDE as well as platformio.
"""

from os import path
import glob
from pathlib import Path
import shutil

'''
1. Copy src directory into a backup folder in case it goes wrong.
2. Go to src directory and find all files within that directory.
3. In each file found:
    i) See if there are any #includes with absolute paths
    ii) convert them to relative paths relative to the file we are looking at
'''

print("Starting relative address conversion...")

path_to_src: str = '../src'

# copy prior directory
backup_directory: str = path.abspath('address_convert_backup')
try:  # try to remove old backup
    shutil.rmtree(backup_directory)
except FileNotFoundError:
    pass
shutil.copytree(path.abspath(path_to_src), backup_directory, dirs_exist_ok=True)  # copy in new backup

# find all directories inside to /src
all_directory_paths: list[str] = glob.glob(path_to_src + '/**/', recursive=True)

# put all banned directories here.
banned_directory_paths: list[str] = []

all_file_paths: list[str] = []
for directory in all_directory_paths:

    # figure out if path is inside a banned directory
    child_path = Path(path.abspath(directory))
    banned = False
    for banned_dir in banned_directory_paths:
        if child_path.is_relative_to(path.abspath(banned_dir)):
            banned = True
            break
    if banned:  # if it is then skip this round of the for loop
        continue

    all_file_paths += glob.glob(directory + '/*.h')
    all_file_paths += glob.glob(directory + '/*.cpp')
    all_file_paths += glob.glob(directory + '/*.hpp')

# create a dict of all file names to their absolute directory
name_path_dict = {}
for file in all_file_paths:
    key = path.basename(file)
    value = path.abspath(file)
    if key in name_path_dict:
        raise Exception("2 files with same name is bad practice!")
    else:
        name_path_dict[key] = value
'''
    The aim is:
    1. open the file as reading
    2. Find all lines that contain "#include" and note their indexes
    3. Modify those lines
    4. Close file and open again as write mode. (overwrite whole file)
    5. Write the whole file in again including modified lines.
    6. Close file
    '''

for file_path in all_file_paths:  # iterate through every file in the 'all_file_paths' list

    absolute_path = path.abspath(file_path)  # get the absolute path of the file

    file = open(absolute_path, 'r')
    file_data = file.readlines()
    file.close()

    replacements = {}

    for ind, line in enumerate(file_data):
        if '#include' in line and '"' in line and 'Arduino.h' not in line:
            included = path.basename(line[1 + line.find('"'):line.rfind('"')])

            # this bit means we ignore global modules that aren't our code eg <string>
            our_code = included in name_path_dict
            if not our_code:
                continue

            full_name = name_path_dict[included]  # full absolute path of the file to include

            abs_path_dir = path.dirname(absolute_path) # The directory part of file we are inspecting
            relative_to_current = path.relpath(full_name,abs_path_dir)  # the relative bit to copy in

            # splice the replacement path into the original line
            replacement = line[:line.find('"')+1] + relative_to_current + line[line.rfind('"'):]

            replacements[ind] = replacement

            if line != replacement:
                print(f"Replaced: {line.strip()} with {replacement.strip()}")

    for line, replacement in replacements.items(): # replace all lines
        file_data[line] = replacement

    # rewrite file
    file = open(absolute_path,'w')
    file.writelines(file_data)
    file.close()

print("Finished relative address conversion.")
