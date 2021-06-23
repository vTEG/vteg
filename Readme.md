When using Windows, this project depends on external video codecs such as the K-Lite Codec pack

Download [here](https://codecguide.com/download_kl.htm)

To build the application yourself, you need [ninja](https://ninja-build.org/) and Qt 5.12.11 or compatible versions.

Build steps on windows:
1. Import the project into Qt Creator and select your x64 compiler
2. Build a version with Qt Creator
3. Get the path of your windeployqt.exe file(<qtdir>/bin/windeploy.exe) and run it in your build dir with the compiled binary as an argument.
Example: C:\Qt\5.12.11\mingw73_64\bin\windeployqt.exe VTEg.exe
