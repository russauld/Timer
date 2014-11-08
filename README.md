Timer
=====

Just like your kitchen timer, but on your computer. Now with moar timerz!
New GUI allows you to create as many timers as you like. They are laid out inside the main window.
They can have unique and meaningful names.
Full count-up functionality has also been added.
Access each timer's menu via the context menu on each timer. The menu includes common count-down values and other options.

There are up and down arrows to set the number of hours, minutes, and seconds to be counted down.
The seconds field of the display can be toggled on or off, along with a more visual progress meter counting down the seconds (or up).

The application can be minimized to the system tray. The tray icon features timer expiration pop-ups.




Build Instructions:
* This is a Qt application. To build it, you'll need Qt and a C++ compiler.
* Run qmake then run make (or nmake for Visual Studio)

Windows Deployment

You need distribute the following DLLs along with the binary:
* QtGui4.dl
* QtCore4.dll
* QtXml4.dll
* QtSvg4.dll
* iconengines/qsvgicon4.dll

This last item is required to get the SVG icons to show in Windows. The application will run without it, but the icons will not appear. It's part of the 'plugins' framework. See %QTDIR%/plugins/iconengines - You may need to build it, see src/plugins/iconengines.
