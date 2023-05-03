#ifndef QTANDROIDNOTIFIER_H
#define QTANDROIDNOTIFIER_H

#include "QAbstractNotifier.h"

class QAndroidNotifier : public QAbstractNotifier
{
public:
    QAndroidNotifier() = default;

public:
    bool show(const QVariant &notificationParameters) override;
};

#endif // QTANDROIDNOTIFIER_H
