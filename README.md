
Steve's Random Number Code

I wrote this code originally *years ago* for a system that did not have stdlib on it

I have carried it around ever since, using it when I needed a pseudo-random number generator.

There are 2 implementations... the original "no stdlib" version and  a newer (but still old)
version that just wraps stdlib random(), seeded by a call to time(NULL).

Both return a floating point value in the range of 0.0 and 1.0

I've only used this for 3D graphics and applications that can tolerate the pseudo-ness of it.

This has *not* been rigorously tested, however it passes the easy "eye test", plotting
a whole bunch of points and seeing that they don't seem to produce obvious patterns.

See the comments in the myrandom.c file for more information.

(c) Copyright 2018 Steve Anderson, all rights reserved.


