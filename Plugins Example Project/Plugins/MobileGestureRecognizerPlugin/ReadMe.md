#Mobile Gesture Recognizers Plugin

In the process of making Republic Sniper, we've built a set of gesture recognizers for touch devices, implemented as Blueprint-spawnable actor components.  The following gesture recognizers are available and ready for use:

- `UTapGestureRecognizer` - a "smart" tap recognizer than can recognize multi-taps (double, triple, etc) without triggering false positives (e.g. no single-tap when double-tap happens), and also supports multi-finger taps (e.g. two-finger double tap).
- `UInstantTapRecognizer` - a not-so-smart but fast recognizer that tells you when any finger touches or leaves the screen. Useful when the delay needed by UTapGestureRecognizer for recognizing multi-taps might be a problem in terms of game play
- `USwipeGestureRecognizer` - a smart swipe recognizer that can recognize horizontal, vertical, diagonal, and edge swipes.
- `UPanGestureRecognizer` - allows you to get notified when fingers move on the screen. Works well, but right now, only a single pan recognizer can be used reliably.

The following gesture recognizers mostly work, but still needs some love:
- `UPinchRotateGestureRecognizer`- A gesture recognizer that notifies when a two-finger pinch or rotate gesture is happening

Future plans include moving the touch-processing code to a shared class to reduce redundant processing and improving the pinch/rotate gesture.

Installation
-------------
Unzip the package into the Plugins directory of your game. To add it as an engine plugin you will need to unzip the module into the plugin directory under where you installed UE4.
