#ifndef QTIOSNOTIFIER_H
#define QTIOSNOTIFIER_H

#include "QAbstractNotifier.h"

class QIosNotifier : public QAbstractNotifier
{
public:
    QIosNotifier();

    bool show(const QVariant &notificationParameters) override;

private:
    void *m_Delegate;
};

#endif // QTIOSNOTIFIER_H
