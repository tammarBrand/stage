QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS+= -L/usr/lib/x86_64-linux-gnu/libjpeg.so -ljpeg
SOURCES += \
        Queue.c \
        capture.c \
        encode.c \
        functions_tools.c \
        main.c \
        rgb_converter.c \
        save_snapshot.c \
        stage.c \
        write_record.c \
        yuv_converter.c

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Queue.h \
    capture.h \
    encode.h \
    functions_tools.h \
    rgb_converter.h \
    save_snapshot.h \
    stage.h \
    write_record.h \
    yuv_converter.h\
    jpeglib.h
