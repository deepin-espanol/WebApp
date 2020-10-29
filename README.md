
# WebApp
WebApp with DTK look and feel

# Image

<img src="https://raw.githubusercontent.com/deepin-espanol/WebApp/main/doc/IMG/WebApp-Example.png">

# Requirements

	qtwebengine5-dev

# Install

	 mkdir build && cd build
	 qmake .. 
	 make

# Use

The "WepApp" file must be executed by terminal, choosing the desired parameters

Parameters:
-h, --help				Displays this menu.

-v, --version          Show version information.

-p, --parser           Enable CommandLineParser. Default is false.

-t, --title (title)    The Title of Application. Default is WepApp.

-u, --url (url)        The target URL. Default is Blank.

-w, --width (width)    The Width of Application. Default is 1024.

-H, --height (height)  The Height of Application. Default is 768.

## example
	./WepApp -t deepines -u https://deepinenespañol.org/
