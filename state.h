#ifndef STATE_H
#define STATE_H

typedef enum {
    ATTR_INIT,
    ATTR_NAME,
    ATTR_VALUE,
    ATTR_EQUEL
}AttrStatus;

typedef enum {
    ATTR_NAME_INIT,
    ATTR_NAME_COPY,
    ATTR_NAME_END,
    ATTR_NAME_STOP
}AttrNameStatus;

#endif
