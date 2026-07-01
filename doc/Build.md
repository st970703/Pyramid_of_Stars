# How to build
Use the `Release` CMake Profile and the hammer icon in CLion.

# Running as Qt widget
- Build executable:

![build_executible](../img/build/build_executable.png)

- Run as Qt widget:

![run_as_qt_widget](../img/build/run_as_qt_widget.png)

# How to package up?
Example:
`& "D:\Qt\6.11.1\mingw_64\bin\windeployqt6.exe" "D:\repo\Learn_CPP\Print_Pyramid\cmake-build-release\Print_Pyramid.exe"`

---
**Suggested by ChatGPT:**

cd D:\repo\Learn_CPP\Print_Pyramid

& "D:\Program Files\JetBrains\CLion 2026.1.3\bin\cmake\win\x64\bin\cmake.exe" --build cmake-build-release

Then package:

New-Item -ItemType Directory -Force dist\Print_Pyramid-windows-x64

Copy-Item cmake-build-release\Print_Pyramid.exe dist\Print_Pyramid-windows-x64\

& "D:\Qt\6.11.1\mingw_64\bin\windeployqt.exe" dist\Print_Pyramid-windows-x64\Print_Pyramid.exe

Compress-Archive -Path dist\Print_Pyramid-windows-x64 -DestinationPath dist\Print_Pyramid-windows-x64.zip -Force

Upload this file to GitHub Releases:

D:\repo\Learn_CPP\Print_Pyramid\dist\Print_Pyramid-windows-x64.zip

---

# Where are the executable files?
## Release version
`Print_Pyramid\cmake-build-release\Print_Pyramid.exe`

## Debug version
`Print_Pyramid\cmake-build-debug\Print_Pyramid.exe`
