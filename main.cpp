#include "QNotification.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QNotification notify;

    QPushButton button("Click me!");
    QObject::connect(&button, &QPushButton::clicked, &button, [&button, &notify] {
        QVariantMap map;
        map["caption"] = "hello";
        map["title"] = "notification";
        map["id"] = 0;

        notify.show(map);
    });
    button.show();

    return QApplication::exec();
}
