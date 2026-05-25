# MP3 Tag Reader and Editor

A Command-Line Interface (CLI) application written in C for reading and editing MP3 ID3v2 tags. 

## 📝 Overview
This tool allows you to easily extract and display embedded metadata (like song title, artist, album, etc.) from `.mp3` files, as well as modify specific tags directly from the terminal without corrupting the underlying audio data.

## ✨ Features
- **View Mode (`-v`)**: Quickly read and display ID3 tags including Title, Artist, Album, Year, Genre, and Comments.
- **Edit Mode (`-e`)**: Seamlessly update specific MP3 metadata tags while preserving the rest of the file's audio and tag data.
- **Cross-Platform**: Can be compiled and run on Windows, Linux, or macOS.

## 🚀 Getting Started

### Prerequisites
- GCC Compiler (or any standard C compiler)

### Compilation
Navigate to the project directory and compile the source files using `gcc`:

```bash
gcc *.c -o mp3_editor
```

*(On Windows, this will generate an `mp3_editor.exe` file)*

### Usage

**1. To View MP3 Tags**
```bash
./mp3_editor -v <filename.mp3>
```
*Example:* `./mp3_editor -v song.mp3`

**2. To Edit an MP3 Tag**
```bash
./mp3_editor -e <modifier> "New Tag Content" <filename.mp3>
```

**Modifiers Available:**
- `-t` : Title (TIT2)
- `-a` : Artist (TPE1)
- `-A` : Album (TALB)
- `-y` : Year (TYER)
- `-c` : Comment (COMM)
- `-g` : Genre (TCON)

*Example:* `./mp3_editor -e -t "My New Title" track.mp3`

## 📂 Project Structure
- `mp3_header.h`: Core definitions, structures, and function prototypes.
- `mp3_main.c`: Application entry point and command-line argument routing.
- `mp3_view.c`: Logic for parsing and displaying ID3v2 tags.
- `mp3_edit.c`: Core logic for safely modifying tags via a temporary file buffering method.
- `functions.c`: Helper functions for tag translations and byte endianness conversions.

## 🤝 Contributing
Contributions, issues, and feature requests are welcome!

## 📄 License
This project is licensed under the [MIT License](LICENSE).
