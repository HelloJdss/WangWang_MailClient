#include "wwmail.h"
#include <QApplication>
#include <QStyleFactory>
#include <QTextCodec>

int main(int argc, char *argv[])
{
  qRegisterMetaType<MimeData>("MimeData");
  qRegisterMetaType<MimeData>("MimeData&");
  qRegisterMetaType<QList<MimeData>>("QList<MimeData>");
  qRegisterMetaType<QList<MimeData>>("QList<MimeData>&");
  QApplication a(argc, argv);
  a.setStyle(QStyleFactory::create("fusion"));
  WwMail w;
  w.show();
  return a.exec();
}
