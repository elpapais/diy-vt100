DIY-VT100
=========

a vt100 hardware clone using MSP430G2553

freenode: #diy-vt100

hardware:
---------
	screenshoots: docs/msp430g2553/screenshoot/
	schematics: docs/msp430g2553/schematics/
	
	flash the firmware: $[sudo] ./build.sh msp430g2553 burn

send a login prompt on diy-vt100:
---------------------------------
*For msp430g2553:*
	$sudo agetty /dev/ttyACM0 9600 vt100
	<sudo part>

Now, on (diy-vt100)terminal:
	<login using username,password>
	$stty cols 16 rows 8

TODO: send login prompt at computer startup

FAQ:
---
Q: Why terminal show everything in on line?
A: Try enabling Auto warp mode (setup B).

Q: Why terminal showing double content in single enter?
A: Try disabling NEW LINE mode (setup B).

How to use!
-----------
* since its a clone of vt100, everything is same(except hardware limitation),
* see [VT100 user guide](http://www.vt100.net/docs/vt100-ug/chapter1.html) for more information.

NOTE:
-----
* use F5 to load setup.
* vt100 had only four Function keys (laymans language).
* you can also use SW2 of MSP430G2 LaunchPad DEV board.
