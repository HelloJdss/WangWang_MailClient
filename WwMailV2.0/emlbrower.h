#ifndef EMLBROWER_H
#define EMLBROWER_H

#include <QWidget>
#include "imapthread.h"
#include <QWebEngineView>

class QWebEngineView;
class MimeData;
namespace Ui {
  class emlBrower;
}
class AttachFile{
public:
  QString Filename;
  QByteArray Filecontent;
};

class emlBrower : public QWidget
{
  Q_OBJECT

public:
  explicit emlBrower(QWidget *parent = 0);
  void setData(const MimeData& eml);
  ~emlBrower();

private slots:
  void on_pushButton_clicked();

  void on_listView_clicked(const QModelIndex &index);

  void on_listView_doubleClicked(const QModelIndex &index);

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_2_clicked();

private:
  void showWindow();
  void baseDecode(QString src,QString Type,QString Encoding);
  void alterDecode(QString src,QString boundary);
  void relatedDecode(QString src,QString boundary);
  void mixedDecode(QString src,QString boundary);
  void distribute(QString src,QString Type,QString boundary,QString Encoding);
  void attachDecode(QString& src,QString Encoding,QString filename);
  bool setView;
  QString ViewContentToReply;
  QString ViewType;
  MimeData* eml;
  QWebEngineView *view;
  Ui::emlBrower *ui;
  QList<AttachFile> AttachList;
signals:
  void deleteMail(qint32,qint32);
  void reply(const QString& From,const QString& To,const QString& Subject,const QString Content);
};

#endif // EMLBROWER_H
