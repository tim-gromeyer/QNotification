#ifndef QTDESKTOPNOTIFIER_H
#define QTDESKTOPNOTIFIER_H

#include "QtAbstractNotifier.h"

#include <QSystemTrayIcon>

class QtDesktopNotifier : public QtAbstractNotifier
{
public:
    QtDesktopNotifier();

    bool show(const QVariant &notificationParameters) override;

private:
    QSystemTrayIcon* m_SystemTrayIcon;
};
#endif // QTDESKTOPNOTIFIER_H
