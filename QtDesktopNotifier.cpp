#include "QtDesktopNotifier.h"

#include <QDebug>
#include <QTimer>
#include <QVariant>

QtDesktopNotifier::QtDesktopNotifier()
{
    m_SystemTrayIcon = new QSystemTrayIcon(QIcon());
}

bool QtDesktopNotifier::show(const QVariant &notificationParameters)
{
    qDebug() << Q_FUNC_INFO << m_SystemTrayIcon->isSystemTrayAvailable();
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon::Information;
    QVariantMap parameters = notificationParameters.toMap();
    QString message = parameters.value("caption", "").toString();
    QString title = parameters.value("title", "").toString();

    m_SystemTrayIcon->show();
#ifdef Q_OS_WIN
    m_SystemTrayIcon->setToolTip(title + "\n" + message);
#endif
    m_SystemTrayIcon->showMessage(title, message, icon, 1000);
    QTimer::singleShot(0, [this] { m_SystemTrayIcon->hide(); });
    return true;
}
