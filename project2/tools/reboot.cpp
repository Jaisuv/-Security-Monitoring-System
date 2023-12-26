#include "reboot.h"

void Reboot::programReboot()
{
    QString program=QApplication::applicationFilePath();
    QStringList arguments=QApplication::arguments();
    QString workingDirectory=QDir::currentPath();
    QProcess::startDetached(program,arguments,workingDirectory);
    QApplication::exit();
}
