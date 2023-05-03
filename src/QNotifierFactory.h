#ifndef QTNOTIFIERFACTORY_H
#define QTNOTIFIERFACTORY_H

#include "QAbstractNotifier.h"

class QNotifierFactory
{
public:
    /// set the Notification class based on operating system
    static QAbstractNotifier *GetPlatformDependencyNotifier();
};

#endif // QTNOTIFIERFACTORY_H
