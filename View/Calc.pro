QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += qwt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    deposit.cpp \
    grafic.cpp \
    main.cpp \
    ../Logic/model.cc \
    qcustomplot.cpp \
    viewer.cpp

HEADERS += \
    ../Logic/Controller.h \
    credit.h \
    deposit.h \
    grafic.h \
    ../Logic/model.h \
    qcustomplot.h \
    viewer.h

FORMS += \
    credit.ui \
    deposit.ui \
    grafic.ui \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    ../s21_calc.h.gch
