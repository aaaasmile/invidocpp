@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64     
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:out/InvidoCode.exe
cl.exe %compilerflags% src/InvidoClient/main.cpp /link %linkerflags%