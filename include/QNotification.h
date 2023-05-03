#ifndef QTNOTIFICATION_H
#define QTNOTIFICATION_H

#include <QObject>

class QAbstractNotifier;

/*!
 * \brief The generic notification wrapper common for all platform
 */
class QNotification : public QObject
{
    Q_OBJECT

public:
    explicit QNotification(QObject *parent = nullptr);
    ~QNotification();

    /// @see QtAbstractNotifier
    Q_INVOKABLE bool show(const QVariant &notificationParameters);

private:
    /// \brief The notifier object which maps to the notification methods for
    /// the respective platforms
    QAbstractNotifier *_Notifier = nullptr;
};

#endif // QTNOTIFICATION_H
