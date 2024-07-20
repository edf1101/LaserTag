"""
This file adds a 'linguist-vendored' tag to the gitattributes file for all folders that we
don't want to be scanned by linguist.

Linguist is a tool that github uses to determine the language of a repository.
We don't want Libraries or image data to be scanned by linguist. so this program fixes that.
"""

from os import path
import glob
from pathlib import Path


def main() -> None:
    """
    This is the main function that runs the linguist vendorer.

    :return: None
    """
    print("Starting linguist vendorer...")

    path_to_src: str = '../src'

    # put all vendored folders here. These must be relative to the src directory.
    misc_vendored_folders: list[str] = ['Hardware/Sound/Sounds',
                                        'Hardware/Displays/Images']
    misc_vendored_folders = [path_to_src + '/' + folder for folder in misc_vendored_folders]

    # find all directories inside to /src. Glob is a recursive search so this will
    # find all directories.
    all_directory_paths: list[str] = glob.glob(path_to_src + '/**/', recursive=True)

    # put all banned directories here. These must be relative to the src directory.
    banned_directory_paths: list[str] = ['Libs/']

    # Go through all the directories and find if any are a child (or lower relative)
    # to a banned directory.
    all_banned_paths: list[str] = []
    for directory in all_directory_paths:

        # figure out if path is inside a banned directory
        child_path = Path(path.abspath(directory))
        banned = False
        for banned_dir in banned_directory_paths:
            banned_dir = path_to_src + '/' + banned_dir
            if child_path.is_relative_to(path.abspath(banned_dir)):
                banned = True
                break
        if banned:  # if it is then skip this round of the for loop
            all_banned_paths.append(directory)
            continue

    file_lines: list[str] = []
    for banned_path in misc_vendored_folders + all_banned_paths:
        relative_path = 'src/' + path.relpath(path.abspath(banned_path), path.abspath(path_to_src))
        file_lines.append(relative_path + '/* linguist-vendored')

    print(f'Found {len(file_lines)} directories to vendor.')

    with open(path_to_src + '/../.gitattributes', 'w', encoding="utf-8") as file:
        file.write('\n'.join(file_lines))

    print("Linguist vendorer complete!")


if __name__ == '__main__':
    main()
