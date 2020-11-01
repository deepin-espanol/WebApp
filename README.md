
  

# WebApp

WebApp with DTK look and feel

  

# Image

  

<img  src="https://raw.githubusercontent.com/deepin-espanol/WebApp/main/doc/IMG/WebApp-Example.png">

  

# Requirements

  

qtwebengine5-dev

  

# Install

  

    mkdir build && cd build
    
    qmake ..
    
    make

  

# Use

  

The "WepApp" file must be executed by terminal, choosing the desired parameters

  

Parameters:

    -h, --help Show this help Message.
    
    -v, --version Show Version info.
    
    -p, --parser Enable CommandLineParser. Default is false.
    
    -t, --title (title) The Title of Application. Default is WebApp.
    
    -u, --url (url) The target URL. Default is Blank.
    
    -w, --width (width) The Width of Application. Default is 1024.
    
    -H, --height (height) The Height of Application. Default is 768
    
    -i, --ico (ico) The ICON of Application.
    
    -d, --desc (desc) The Description of Application.
    
    -c, --cfg (cfg) The Configuration file of Application.
    
    -r, --root (root) The root path of the program web service.
    
    -P, --port (port) The port number of the program web service.

  

## example

./WepApp -t "Deepin en Español" -u https://deepinenespañol.org/