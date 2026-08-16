# MP3 Tag Reader and Editor

A Command-Line Argument (CLA) application written in C for reading and editing MP3 ID3v2 tags. 

## 📝 Overview
This tool allows you to easily extract and display embedded metadata (like song title, artist, album, etc.) from `.mp3` files, as well as modify specific tags directly from the terminal without corrupting the underlying audio data.

## 🎥 Video Demo

The demonstration video is located in the `src/` directory. You can watch it right here:

<video src="./src/demo.mp4" width="800" controls>
  Your browser does not support the video tag.
</video>

*(Note: If the video does not load, ensure `demo.mp4` is present in the `src/` folder of this repository)*

## ✨ Features
- **View Mode (`-v`)**: Quickly read and display ID3 tags including Title, Artist, Album, Year, Genre, and Comments.
- **Edit Mode (`-e`)**: Seamlessly update specific MP3 metadata tags while preserving the rest of the file's audio and tag data.
- **Cross-Platform**: Can be compiled and run on Windows, Linux, or macOS.

## 🚀 Getting Started

### Prerequisites
- GCC Compiler (or any standard C compiler)

### Compilation
Navigate to the project root directory and compile the source files located in `src/` using `gcc`:

```bash
gcc src/*.c -o MP3
```

*(On Windows, this will generate an `MP3.exe` file)*

### Usage

**1. To View MP3 Tags**
```bash
./MP3 -v <filename.mp3>
```
*Example:* `./MP3 -v src/sample.mp3`

**2. To Edit an MP3 Tag**
```bash
./MP3 -e <modifier> "New Tag Content" <filename.mp3>
```

**Modifiers Available:**
- `-t` : Title (TIT2)
- `-a` : Artist (TPE1)
- `-A` : Album (TALB)
- `-y` : Year (TYER)
- `-c` : Comment (COMM)
- `-g` : Genre (TCON)

*Example:* `./MP3 -e -t "My New Title" src/sample.mp3`

## 📂 Project Structure
The source code and assets are located in the `src/` directory:
- `src/mp3_header.h`: Core definitions, structures, and function prototypes.
- `src/mp3_main.c`: Application entry point and command-line argument routing.
- `src/mp3_view.c`: Logic for parsing and displaying ID3v2 tags.
- `src/mp3_edit.c`: Core logic for safely modifying tags via a temporary file buffering method.
- `src/functions.c`: Helper functions for tag translations and byte endianness conversions.
- `src/demo.mp4`: Demonstration video showing the tool in action.
- `src/sample.mp3`: A sample file to test the view and edit functionalities.

## 🤝 Contributing
Contributions, issues, and feature requests are welcome!

## 📄 License
This project is licensed under the [MIT License](LICENSE).
