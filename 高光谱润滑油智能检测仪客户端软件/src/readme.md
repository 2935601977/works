# 部分源码


# 1、编译

```shell
编译rc资源文件
e:\SETUP\msys64\mingw64\bin\windres.exe ..\src\PgResource\version.rc -o ..\src\PgResource\version.o


D:\msys64\mingw64\bin\cmake.exe .. -G "MinGW Makefiles"
D:\msys64\mingw64\bin\\mingw32-make.exe
```

# 2、Qt工程自动打包

```shell
d:\DCG\work\Progoo\Y2023\08_PgLube\Src\PgSpecDetClient\trunk\vendor\QT5.5.0_MinGW510_X64\bin\windeployqt.exe d:\DCG\work\Progoo\Y2023\08_PgLube\Src\PgSpecDetClient\trunk\bin\Release\PG_SDC_GUI.exe
```

```shell
D:\FFFFF\Progoo\PgProject\PgSpecDetClient\vendor\QT5.5.0_MinGW510_X64\bin\windeployqt.exe D:\FFFFF\Progoo\PgProject\PgSpecDetClient\bin\Debug\PG_SDC_GUI.exe
```
