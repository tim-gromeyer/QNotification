#include "QAbstractNotifier.h"

class QWebassemblyNotifier : public QAbstractNotifier
{
public:
    QWebassemblyNotifier() = default;

public:
    bool show(const QVariant &notificationParameters);
};
