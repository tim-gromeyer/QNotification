#include "QtNotification.h"
#include "QtNotifierFactory.h"

QtNotification::QtNotification(QObject *parent)
    : QObject(parent)
    , _Notifier(QtNotifierFactory::GetPlatformDependencyNotifier())
{}

QtNotification::~QtNotification()
{
    delete _Notifier;
}

bool QtNotification::show(const QVariant &notificationParameters)
{
    return _Notifier->show(notificationParameters);
}
