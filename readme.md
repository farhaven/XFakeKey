XFakeKey
========

About
-----
`XFakeKey` fakes X keypresses. The keysyms to press/release are read from stdin or from the commandline.

How to build it
---------------
Simply running `make` in the source directory should be enough. The file `xfk` contains the complete binary. Note: Static linking 
is a bit problematic at the moment because a few needed XCB symbols are not properly exported in regular XCB libraries (such as 
`xcb_auth`) and because glibc appearently doesn't exactly get what 'static linking' means (i.e. even if static linking is done, 
the original library is still required at runtime to use `gethostbyname`).

How to use it
-------------
There are two ways to run XFakeKey. The first is piping keysyms into stdin, the second involves passing command parameters. If a 
keysym is prefixed with a `+`, only a `key_press` event is generated. If the prefix is `-`, a `key_release` is generated. Else a 
`key_press` is shortly after followed by a `key_release`. This can be used to trigger key combinations, such as the following:

    ./xfk
    +XK_Meta_L
    XK_2
    -XK_Meta_L

or

    ./xfk +XK_Meta_L XK_2 -XK_Meta_L

This emulates a user pressing Alt+2. XFakeKey first tries to use `$DISPLAY` to get the X display to connect to. If that fails, 
`:0.0` is used as a fallback.
