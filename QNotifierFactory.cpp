#include "QtNotifierFactory.h"

#if defined Q_OS_ANDROID
#include "QtAndroidNotifier.h"
#elif defined Q_OS_IOS
#include "QtIOSNotifier.h"
#elif defined Q_OS_WASM
#include "wasm/notification.h"
#else
#include "QtDesktopNotifier.h"
#endif

QtAbstractNotifier *QtNotifierFactory::GetPlatformDependencyNotifier()
{
#if defined Q_OS_ANDROID
    return new QtAndroidNotifier();
#elif defined Q_OS_IOS
    return new QtIosNotifier();
#elif defined Q_OS_WASM
    return new QtWasmNotifier();
#else
    return new QtDesktopNotifier();
#endif
}
