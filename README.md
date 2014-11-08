Timer
=====

Just like your kitchen timer, but on your computer!

There are up and down arrows to set the number of hours, minutes, and seconds to be counted down.
The seconds field of the display can be toggled on or off, along with a more visual progress meter counting down the seconds (or up).
You can count up by pressing start when the timer value is zero.

The application can be minimized to the system tray. The tray icon features timer expiration pop-ups and a quick menu to set common count-down values and other options.

Multiple instances of the application can be run, each with a different name.
This can be useful when you want to track time spent on different projects. 
You can set the name by using either the Option menu in the GUI or via tray icon's menu.

This is a Qt application. To build it, you'll need Qt and a C++ compiler.

Build Instructions:
* Run qmake then run make (or nmake for Visual Studio)

Windows deployment:
You need distribute the following DLLs along with the binary:
QtGui4.dl
QtCore4.dll
QtXml4.dll
QtSvg4.dll
iconengines/qsvgicon4.dll

This last item is required to get the SVG icons to show in Windows. The application will run without it, but the icons will not appear.
It's part of the 'plugins' framework. See %QTDIR%/plugins/iconengines - You may need to build it, see src/plugins/iconengines.
