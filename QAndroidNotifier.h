#ifndef QTANDROIDNOTIFIER_H
#define QTANDROIDNOTIFIER_H

#include "QtAbstractNotifier.h"

class QtAndroidNotifier : public QtAbstractNotifier
{
public:
    QtAndroidNotifier() {}

public:
    bool show(const QVariant &notificationParameters) override;
};

#endif // QTANDROIDNOTIFIER_H
