### Realtime Rendering Demos

在阅读[Real-Time Rendering, Fourth Edition](https://book.douban.com/subject/30296179/), 简称RTR4时，根据书中原理编写的Demo。

> 我的RTR4的读书笔记写在知乎专栏:[RealtimeRendering](https://zhuanlan.zhihu.com/RealtimeRendering4th)

我打算先逐步搭建必要的渲染环境: 如照相机、鼠标控制、光照模型等，然后渲染出静态水、流动水、大海等效果。会先使用QT封闭好的变换矩阵、照相机等，然后根据书中原原理自己编写。

**开发环境:** 
win10 + QT+OpenGL

> QT版本: [qt-opensource-windows-x86-5.14.0.exe](http://mirror.bit.edu.cn/qtproject/archive/qt/5.14/5.14.0/qt-opensource-windows-x86-5.14.0.exe)

关于QT和OpenGL的结合，可查看教程: [QT OpenGL](http://www.digitalfanatics.org/projects/qt_tutorial/chapter14.html)


如果调试时无法生成debugger，找不到cdb.exe，可以通过按钮WinSDK(按装时要选择Debugging tools): [winsdksetup.exe](https://download.microsoft.com/download/4/2/2/42245968-6A79-4DA7-A5FB-08C0AD0AE661/windowssdk/winsdksetup.exe)
