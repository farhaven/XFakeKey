#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#include "keytable.h"

#define LINELENGTH 256
#define KEYDELAY (125 * 1000)

typedef enum {
    MODE_BOTH,
    MODE_PRESS,
    MODE_RELEASE
} keypress_mode;

Display *dpy;

int
find_keysym(char *name) {
    int i;
    for(i = 0; keynames[i].name != NULL; i++) {
        if (!strncmp(keynames[i].name, name, LINELENGTH))
            return keynames[i].keysym;
    }
    return 0;
}

int
fake_keypress(int keysym, keypress_mode m) {
    int kc = XKeysymToKeycode(dpy, keysym);
    if (kc == 0) return 0;

    if ((m == MODE_BOTH) || (m == MODE_PRESS))
        XTestFakeKeyEvent(dpy, kc, 1, 0); /* press */
    if ((m == MODE_BOTH) || (m == MODE_RELEASE))
        XTestFakeKeyEvent(dpy, kc, 0, 0); /* and immediately release */
    XFlush(dpy);
    return 1;
}

int
main(int argc, char **argv) {
    int arg_idx = 0;
    char *dpy_name = XDisplayName(NULL);
    dpy = XOpenDisplay(dpy_name);
    if (dpy == NULL) {
        dpy_name = XDisplayName(":0.0");
        dpy = XOpenDisplay(dpy_name);
    }
    if (dpy == NULL) {
        fprintf(stderr, "failed to open dpy %s\n", XDisplayName(NULL));
        exit(1);
    }

    while ((!feof(stdin)) && (arg_idx <= argc)) {
        char *line = (char *)calloc(sizeof(char), LINELENGTH);
        if (++arg_idx < argc) {
            strncpy(line, argv[arg_idx], strlen(argv[arg_idx]));
        } else if (argc == 1)
            fgets(line, LINELENGTH, stdin);
        if (line[0] == '\0') { /* empty line (i.e. not even a \n) usually means ^D was pressed or EOF reached */
            free(line);
            break;
        }

        /* remove trailing newline from line */
        char *p = strchr(line, '\n');
        if (p) *p = '\0';
        
        keypress_mode mode = MODE_BOTH;
        if (*line == '+') {
            mode = MODE_PRESS;
            line++;
        } else if (*line == '-') {
            mode = MODE_RELEASE;
            line++;
        }

        fprintf(stderr, "%s%s\n", line, (mode == MODE_PRESS) ? " (p)" : (mode == MODE_RELEASE) ? " (r)" : "");

        if (!fake_keypress(find_keysym(line), mode)) {
            fprintf(stderr, "could not assign a keycode to \"%s\"\n", line);
        }
        if (mode == MODE_BOTH)
            free(line);
        else
            free(--line);

        usleep(KEYDELAY);
    }

    return 0;
}
