#include "QNotifierFactory.h"

#if defined Q_OS_ANDROID
#include "android/QAndroidNotifier.h"
#elif defined Q_OS_IOS
#include "ios/QIOSNotifier.h"
#elif defined Q_OS_WASM
#include "wasm/notification.h"
#else
#include "desktop/QDesktopNotifier.h"
#endif

QAbstractNotifier *QNotifierFactory::GetPlatformDependencyNotifier()
{
#if defined Q_OS_ANDROID
    return new QAndroidNotifier();
#elif defined Q_OS_IOS
    return new QIosNotifier();
#elif defined Q_OS_WASM
    return new QWebassemblyNotifier();
#else
    return new QDesktopNotifier();
#endif
}
