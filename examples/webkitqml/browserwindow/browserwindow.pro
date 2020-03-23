TEMPLATE = app

QT += quick webkit-private quick-private
SOURCES += main.cpp

mac: CONFIG -= app_bundle

target.path = $$[QT_INSTALL_EXAMPLES]/webkitqml/browserwindow
INSTALLS += target
