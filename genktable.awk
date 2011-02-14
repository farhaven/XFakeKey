#!/bin/awk -F' '

BEGIN {
    print "#define XK_MISCELLANY"
    print "#define XK_XKB_KEYS"
    print "#define XK_3270"
    print "#define XK_LATIN1"
    print "#define XK_LATIN2"
    print "#define XK_LATIN3"
    print "#define XK_LATIN4"
    print "#define XK_LATIN8"
    print "#define XK_LATIN9"
    print "#define XK_KATAKANA"
    print "#define XK_ARABIC"
    print "#define XK_CYRILLIC"
    print "#define XK_GREEK"
    print "#define XK_TECHNICAL"
    print "#define XK_SPECIAL"
    print "#define XK_PUBLISHING"
    print "#define XK_APL"
    print "#define XK_HEBREW"
    print "#define XK_THAI"
    print "#define XK_KOREAN"
    print "#define XK_ARMENIAN"
    print "#define XK_GEORGIAN"
    print "#define XK_CAUCASUS"
    print "#define XK_VIETNAMESE"
    print "#define XK_CURRENCY"
    print "#define XK_MATHEMATICAL"
    print "#define XK_BRAILLE"
    print
    print "#include <X11/XF86keysym.h>"
    print "#include <X11/keysymdef.h>"
    print
    print "struct {"
    print "    int keysym;"
    print "    const char *name;"
    print "} keynames[] = {"
}

/^#define/ {
    gsub("[[:space:]]+", " ")
    print "    { " $2 ", \"" $2 "\" },"
}

END {
    print "    { 0, NULL }"
    print "};"
}
