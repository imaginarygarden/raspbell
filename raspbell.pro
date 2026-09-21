QT += widgets
requires(qtConfig(filedialog))

HEADERS             = mainwindow.h
SOURCES             = main.cpp \
                      mainwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/desktop/raspbell
INSTALLS += target