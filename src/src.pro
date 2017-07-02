TARGET = project

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG -= debug_and_release

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)

DEST = $$OUT_PWD/
win32:DEST ~= s,/,\\,g
for (FILE, FILES) {
	win32:FILE ~= s,/,\\,g
	QMAKE_POST_LINK += $$QMAKE_COPY $$shell_quote($$FILE) $$shell_quote($$DEST) $$escape_expand(\\n\\t)
}

PATH_TO_LIB = $$PWD/'../libs/lib'
PATH_TO_INCLUDE = $$PWD/'../libs/include'

INCLUDEPATH += ../bullet/
LIBS += "$${OUT_PWD}/../bullet/libBULLET.a"

INCLUDEPATH += $$PATH_TO_INCLUDE'/GL'
LIBS += -L$$PATH_TO_LIB -lglew32
PRE_TARGETDEPS += $$PATH_TO_LIB'/libglew32.a'

INCLUDEPATH += $$PATH_TO_INCLUDE'/GLFW'
LIBS += -L$$PATH_TO_LIB -lglfw3

INCLUDEPATH += $$PATH_TO_INCLUDE
LIBS += -L$$PATH_TO_LIB -lopengl32
LIBS += -L$$PATH_TO_LIB -lglu32
LIBS += -L$$PATH_TO_LIB -lgdi32
