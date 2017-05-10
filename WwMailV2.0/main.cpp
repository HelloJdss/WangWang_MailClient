#include "wwmail.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
  qRegisterMetaType<QList<MimeData>>("QList<MimeData>");
  qRegisterMetaType<QList<MimeData>>("QList<MimeData>&");
  QApplication a(argc, argv);
  a.setStyle(QStyleFactory::create("fusion"));
  WwMail w;
  w.show();
  return a.exec();
}
