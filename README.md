Keywords Grabber is a straightforward C++ program crafted for educational purposes. It enables users to peruse the contents of either a single file or all files within a designated folder, extracting lines containing specified keywords.

## Features

- Read the contents of a single file.
- Read the contents of all files within a selected folder.
- Cross-platform compatibility for Windows and Unix-like systems.

## Requirements

- C++ compiler compatible with C++11 standard.
- For Windows:
  - Windows SDK for `SHBrowseForFolder` and `SHGetPathFromIDList` functions.
- For Unix-like systems:
  - GTK library for file dialog functionality.

## Usage

1. Clone the repository:

    ```
    git clone https://github.com/9de/keywords-grabber.git
    ```

2. Compile the program:

    ```
    g++ main.cpp -o keywordsgrabber -std=c++11
    ```

3. Run the executable:

    ```
    ./keywordsgrabber
    ```

4. Follow the on-screen instructions to choose between reading a single file or all files in a folder.

## Contributing

Contributions are welcome! If you find any bugs or want to add new features, feel free to open an issue or submit a pull request.

## License and Disclaimer

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details. 

**Disclaimer:** This project is provided for educational purposes only. The author assumes no responsibility or liability for any misuse or damage caused by the software.

