# Task Manager

A simple terminal task manager. It was designed to be used as a windows shortcut so I can quickly add/track tasks without the slowness and bloat of task management apps. As such, the app is designed for windows solely. 

### App Setup:

The app requires a file named "tasks.txt" to read and write tasks to. It also requires a file named "tasks-archive.txt" to archive tasks. I've included files called "tasks-template.txt" and "tasks-archive-template.txt" which you can rename appropriately.

### Shortcut Setup:

Generate the executable from the repository by running `make`. 

Right click the executable in file explorer or the desktop and select "Pin to Start." Navigate to your start menu path and right click the executable's shortcut. Assign the global shortcut keys to whatever you'd like and apply the change. Now you can open the app anytime on your computer.