#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QMetaType>
#include <QMutex>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QTextStream>
#include <QCoreApplication>

#include "rcrtc_constants.h"
#include "rcrtc_engine.h"

int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN
    ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if QT_VERSION_MAJOR == 5 && QT_VERSION_MINOR >= 14
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#else
#ifdef Q_OS_LINUX // X11
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#endif
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    QApplication a(argc, argv);

    qRegisterMetaType<rc_connection_status>("rc_connection_status");
    qRegisterMetaType<rcrtc::RCRTCMediaType>("rcrtc::RCRTCMediaType");
    qRegisterMetaType<QList<QString>>("QList<QString>");
    qRegisterMetaType<rcrtc::RCRTCRole>("rcrtc::RCRTCRole");

    MainWindow w;
    w.show();
    return a.exec();
}
