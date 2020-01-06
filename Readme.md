### Realtime Rendering Demos

在阅读[Real-Time Rendering, Fourth Edition](https://book.douban.com/subject/30296179/)(简称RTR4)时，根据书中原理编写的Demo。

> 我的RTR4的读书笔记写在知乎专栏:[RealtimeRendering](https://zhuanlan.zhihu.com/RealtimeRendering4th)

我打算先逐步搭建必要的渲染环境: 如照相机、鼠标控制、光照模型等，然后渲染出静态水、流动水、大海等效果。会先使用QT封闭好的变换矩阵、照相机等，然后根据书中原原理自己编写。

**开发环境:** 
win10 + QT+OpenGL

> QT版本: [qt-opensource-windows-x86-5.14.0.exe](http://mirror.bit.edu.cn/qtproject/archive/qt/5.14/5.14.0/qt-opensource-windows-x86-5.14.0.exe)。如果调试时无法生成debugger，找不到cdb.exe，可以通过按装WinSDK(按装时要选择Debugging tools): [winsdksetup.exe](https://download.microsoft.com/download/4/2/2/42245968-6A79-4DA7-A5FB-08C0AD0AE661/windowssdk/winsdksetup.exe)

项目中DefaultModels目录下，以点.vs结尾的是vertex shader代码，以.fs结尾的是fragment shader代码，[.off](https://shape.cs.princeton.edu/benchmark/documentation/off_format.html)模型文件。我写了一个简单的.off解析工具放在项目的Utilities目录下的modelParser.h中，其中的helpferFuncs.h中包含一些定制的文件读取工具及log打印工具。
> [这里](https://learnopengl.com/)可以学习一些基本的openGL和图形学知识。
