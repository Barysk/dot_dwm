# DWM config, made for My devices

An example of how this config looks
![An image of how it looks](example.png)

[Map of dwm patches](http://coggle.it/diagram/X9IiSSM6PTWOM9Wz/t/dwm-patches-last-tallied-2024-09-27/d3448968e2509321527c3864cd4eee651e5f55e525582fdbf33be764972d9aef)

This build uses:
* dwm - window manager
    * activemonitor
    * actualfullscreen
    * alwayscenter
    * attachbottom
    * bottomstack
    * centerstack
    * colorschemes
    * fullgaps
    * movestack
    * pertag_with_sel
    * statusallmons
    * swapmonitors
    * systray
* dwmblocks - same as slstatus but better
* dmenu - application menu
* j4-dmenu-desktop - wraper for dmenu
* kitty - terminal emulator
* betterlockscreen - lockscreen
* mpv - media player
* picom - compositor
* feh - wallpaper
* flameshot - for screenshots

also applyed this to make borders non-transparent:
drw.c
```
	if (!XftColorAllocName(drw->dpy, DefaultVisual(drw->dpy, drw->screen),
	                       DefaultColormap(drw->dpy, drw->screen),
	                       clrname, dest))
		die("error, cannot allocate color '%s'", clrname);
+
+	dest->pixel |= 0xff << 24;
}
}
```
