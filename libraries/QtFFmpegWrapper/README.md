# QTFFmpegWrapper Demo (2015 x64)

This wrapper is an updated version of the QTFFmpegWrapper made by Daniel Roggen:
https://github.com/icemanpro/QtFFmpegWrapper
https://code.google.com/p/qtffmpegwrapper/

I did this porting because I needed this wrapper for an university project.

### HOW TO OPEN

You can open the project by using:
- Qt Creator, open the .pro file
- VS2013 (or after), by opening the .sln file or by opening/importing 
  the .pro file with the Visual Studio Qt Plugin that you can find 
  easily online

### CHANGES

	FFmpeg git-a254452 2011-09-19	->	FFmpeg git-0671dc5 2015-07-22
	32 bit FFmpeg libs				->	64 bit FFmpeg libs
	Internal console for debugging	->	qDebug() for debugging
	Added "seek to previous frame"
	
### LICENSE
	
The following files are under the BSD LICENSE as explained in Roggen's project:

	ffmpeg.h
	mainwindow.cpp
	mainwindow.h
	QVideoEncoder.cpp
	QVideoDecoder.cpp
	QVideoEncoder.h
	QVideoDecoder.h
