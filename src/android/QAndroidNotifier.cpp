#include "QAndroidNotifier.h"

#include <QVariant>
#if QT5
#include <QtAndroid>
#define JniObject QAndroidJniObject
#else
#include <QJniObject>
#define JniObject QJniObject
#endif

bool QAndroidNotifier::show(const QVariant &notificationParameters)
{
    QVariantMap parameters = notificationParameters.toMap();
    QString caption = parameters.value(QStringLiteral("caption"), "").toString();
    QString title = parameters.value(QStringLiteral("title"), "").toString();
    int id = parameters.value(QStringLiteral("id"), 0).toInt();

    JniObject jni_caption = JniObject::fromString(caption);
    JniObject jni_title = JniObject::fromString(title);

    JniObject::callStaticMethod<void>("com/notification/javalib/QtAndroidNotification",
                                      "show",
                                      "(Ljava/lang/String;Ljava/lang/String;I)V",
                                      jni_title.object<jstring>(),
                                      jni_caption.object<jstring>(),
                                      static_cast<jint>(id));
    return true;
}
