TARGET = powermenu-daemon
target.path = /usr/bin

QT += dbus

CONFIG += sailfishapp link_pkgconfig
PKGCONFIG += sailfishapp mlite5

dbus.files = dbus/org.coderus.powermenu.service
dbus.path = /usr/share/dbus-1/services

systemd.files = systemd/powermenu.service
systemd.path = /usr/lib/systemd/user

mce.files = mce/90-powermenu-keys.ini
mce.path = /etc/mce

lipstick.files = \
    lipstick/PowerMenuDialog.qml \
    lipstick/lipstick.patch
lipstick.path = /usr/share/powermenu-gui/data

INSTALLS = target systemd mce lipstick dbus

SOURCES += \
    src/dbuslistener.cpp \
    src/main.cpp

HEADERS += \
    src/dbuslistener.h
