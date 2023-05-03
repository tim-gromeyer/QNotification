#ifndef QDesktopNotifier_H
#define QDesktopNotifier_H

#include "QAbstractNotifier.h"

#include <QSystemTrayIcon>

class QDesktopNotifier : public QAbstractNotifier
{
public:
    QDesktopNotifier();

    bool show(const QVariant &notificationParameters) override;

private:
    QSystemTrayIcon* m_SystemTrayIcon;
};
#endif // QDesktopNotifier_H
