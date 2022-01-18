# android 反汇编工具一把梭(要你命3000)

1. 集成 [Apktool_2.6.0](https://github.com/iBotPeaches/Apktool/releases)
2. 集成 [jd-gui.exe](http://java-decompiler.github.io/)
3. 集成 [dex-tools-2.2](https://github.com/pxb1988/dex2jar/releases)
4. 修改dex-tools-2.2 中的 d2j_invoke.bat文件如下

```bat
@echo off
REM better invocation scripts for windows from lanchon, release in public domain. thanks!
REM https://code.google.com/p/dex2jar/issues/detail?id=192

setlocal enabledelayedexpansion

set LIB=%~dp0lib

set CP=
for %%X in ("%LIB%"\*.jar) do (
    set CP=!CP!%%X;
)

java -Xms2048m -Xmx4096m -cp "%CP%" %*
```

# 参考链接
[dex2jar反编译多个dex的apk方法以及常见错误...](https://blog.csdn.net/u011623002/article/details/106336306)