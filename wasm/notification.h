#include "QtAbstractNotifier.h"

class QtWasmNotifier : public QtAbstractNotifier
{
public:
    QtWasmNotifier() = default;

public:
    bool show(const QVariant &notificationParameters);
};
