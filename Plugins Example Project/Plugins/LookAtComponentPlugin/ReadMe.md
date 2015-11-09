Description
-----------
This plugin adds a new movement component that can be added to any actor. This movement component will cause the object to always orient itself toward the local player, another actor, or a world location.

Why
---
Although the look-at logic is fairly simple, we found ourselves repeatedly implementing the same logic to orient a turret, camera, or other object toward the player or another actor. It seemed logical to wrap it up into an engine plugin so that the logic would exist in a single place.

Installation
-------------
Unzip the package into the Plugins directory of your game. To add it as an engine plugin you will need to unzip the module into the plugin directory under where you installed UE4.

1. Add the `Look At Movement Component` to an actor.
2. Configure in the inspector to specify whether the actor should look at the local player, another actor, or a specific world location.
3. There is no step 3. You're done.

Contact
-------------
If you have any Questions, Comments, Bug reports or feature requests for this plugin, or you wish to contact me you can and should email me - jeff@martiancraft.com


License
-------

Copyright (c) 2015, MartianCraft & Jeff LaMarche

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so. 

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.