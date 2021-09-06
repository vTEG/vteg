This project is still WIP!

# vTEG

vTEG is a C++ application for watching, analysing and tagging videos, so you could jump back and forth between the most important parts of the video. You can either save/load tags from our own .vteg format, or load/write them from and to .CSV files, for compatibility with other tagging software.

## Download
Fully compiled binarys will be linked here when available

## Building

First of all, you need [Qt](https://www.qt.io/download) to build vTEG. We're using the open source version. You also need to install mingw 64bit from the Qt installer with it. We've build the project with Qt V5.12.11, so having a somewhat similar version installed might be helpful.

If you're using windows, you also need an external video codec, because Qt's multimedia library won't work otherwise. In development, we've used [K-Lite Codec Pack Standard](https://codecguide.com/download_k-lite_codec_pack_standard.htm).
Mac and Linux should be able to handle this natively.

M1 Macs are currently not supported!

Also, you need [Ninja](https://github.com/ninja-build/ninja/releases) as a build tool for cmake and [CMAKE](https://cmake.org/download/) itself.

### Build Steps

You need to replace these placeholders:
1. PATH-TO-QT
2. QT-VERSION
3. MINGW64-VERSION

With your own paths to the installations. Please also ONLY use the compile tools delivered by the Qt installation. Using another g++ compiler for example will just throw tons of errors.

```bash
git clone https://github.com/vTEG/vteg

# Open CMakeLists.txt and change line 8 to your local Qt installation path
# Open folder in terminal

mkdir build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE:STRING=Release -DQT_QMAKE_EXECUTABLE:STRING=PATH-TO-QT/QT-VERSION/MINGW64-VERSION/bin/qmake.exe -DCMAKE_C_COMPILER:STRING=PATH-TO-QT/Tools/MINGW64-VERSION/bin/gcc.exe -DCMAKE_CXX_COMPILER:STRING=PATH-TO-QT/Tools/MINGW64-VERSION/bin/g++.exe
cmake --build . --target all
```

### Working example build config

```bash
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE:STRING=Release -DQT_QMAKE_EXECUTABLE:STRING=C:/Qt/5.12.11/mingw73_64/bin/qmake.exe -DCMAKE_C_COMPILER:STRING=C:/Qt/Tools/mingw730_64/bin/gcc.exe -DCMAKE_CXX_COMPILER:STRING=C:/Qt/Tools/mingw730_64/bin/g++.exe
cmake --build . --target all
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
