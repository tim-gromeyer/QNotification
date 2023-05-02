#include "wasm/notification.h"

#include <QVariant>

#include <emscripten.h>

void show_notification(const char *title, const char *description, const char *icon)
{
    char script[1024];
    snprintf(script,
             sizeof(script),
             "if (Notification.permission === 'granted') {"
             "  new Notification('%s', { body: '%s', icon: '%s' });"
             "} else if (Notification.permission !== 'denied') {"
             "  Notification.requestPermission().then(permission => {"
             "    if (permission === 'granted') {"
             "      new Notification('%s', { body: '%s', icon: '%s' });"
             "    }"
             "  });"
             "}",
             title,
             description,
             icon,
             title,
             description,
             icon);

    emscripten_run_script(script);
}

bool QtWasmNotifier::show(const QVariant &notificationParameters)
{
    QVariantMap parameters = notificationParameters.toMap();
    QString message = parameters.value(QStringLiteral("caption"), "").toString();
    QString title = parameters.value(QStringLiteral("title"), "").toString();

    show_notification(title.toUtf8(), message.toUtf8(), "");
    return true;
}
