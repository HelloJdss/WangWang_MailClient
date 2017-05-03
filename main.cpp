#include "clientwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setStyle(QStyleFactory::create("fusion"));
  ClientWindow w; //启动主界面
  w.move((QApplication::desktop()->width() - w.width()) / 2,
         (QApplication::desktop()->height() - w.height()) / 2);
  if (!w.isLogin()) {
    QMessageBox::warning(&w, QObject::tr("警告！"), ("用户未成功登入！"),
                         QMessageBox::Yes); //警告对话框
    return 0;
  }
  w.show();
  return a.exec();
}
