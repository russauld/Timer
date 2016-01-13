Timer
=====

This software implements a timer application similar to a kitchen timer.
It allows you to create as many timers as you like and choose how they are laid out inside the main window.
Each timer can have unique and meaningful names, and each timer can count up or down. When the timer is counting down, an alert is generated when the timer expires, via either a pop-up message or a system tray notification.
Each timer's menu can be accessed via a right-click context menu on each timer. The menu includes common count-down values and other options, such as setting the name.
The timers can be used in an exclusive "radio button" mode, meaning that only one timer can be active at a time.
In this mode, if a timer is started, the other timers will be stopped.
Combined with count-up mode, this can be used to track time spent on different projects. Create a timer for each project and give it a meaningful name, set it to count-up mode, enable radio mode, then click start on each timer when spending time on that project. When you switch to a different project, just click start on the appropriate timer and the other one will stop.

The software now saves the window size and location, the timers and their names, and the layout of the timers.

There are up and down arrows to set the number of hours, minutes, and seconds to be counted down. The time can also be set using a dialog box.
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
