#include "QNotification.h"
#include "QAbstractNotifier.h"
#include "QNotifierFactory.h"

QNotification::QNotification(QObject *parent)
    : QObject(parent)
    , _Notifier(QNotifierFactory::GetPlatformDependencyNotifier())
{}

bool QNotification::show(const QVariant &notificationParameters)
{
    return _Notifier->show(notificationParameters);
}

QNotification::~QNotification()
{
    delete _Notifier;
}
