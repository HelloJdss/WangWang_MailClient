#include "emlbrower.h"
#include "ui_emlbrower.h"
#include <QTextCodec>
#include <QWebEngineSettings>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QFileDialog>

emlBrower::emlBrower(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::emlBrower)
{
  ui->setupUi(this);

  view = new QWebEngineView(this);
  QPalette palette;
  palette.setBrush(QPalette::Background,QBrush(Qt::white));
  ui->MiMEWidget->setPalette(palette);
  ui->MiMEWidget->setAutoFillBackground(true);
  QGridLayout *layout = new QGridLayout(ui->MiMEWidget);
  layout->addWidget(view);
  setView=false;
  QStandardItemModel* MailFolderTree = new QStandardItemModel(ui->listView); //父对象为ui->treeView，智能释放
  this->ui->listView->setModel(MailFolderTree);
  ui->pushButton->setEnabled(false);
  ui->pushButton_2->setEnabled(false);
}

void emlBrower::setData(const MimeData &eml)
{
  this->eml = new MimeData(eml);
  ui->lineEdit_date->setText(eml.getDate());
  ui->lineEdit_from->setText(eml.getFrom());
  ui->lineEdit_subject->setText(eml.getSubject());
  ui->lineEdit_to->setText(eml.getTo());
  this->setWindowTitle(eml.getSubject()+"  From: "+eml.getFrom());
  showWindow();
}


void emlBrower::showWindow()
{
  QByteArray s=QString(eml->getBody().left(eml->getBody().size()-5)).toLatin1(); //去除结尾的)
  distribute(s,eml->getHeaderType(),eml->getHeaderBoundary(),eml->getHeaderEncoding());
}

void emlBrower::baseDecode(QString src,QString Type,QString Encoding)
{
  //简单类型的话直接显示
  QByteArray s = src.toLatin1();
  QByteArray sub_utf;
  if (Encoding.toUpper().contains("BASE64")) sub_utf = QByteArray::fromBase64(s);
  else if (Encoding.toUpper().contains("QUOTED"))  sub_utf = eml->DecodequotedPrintable(s);
  else sub_utf = s;
  view->setContent(sub_utf,Type.remove("\""));
  QRegularExpression rx("charset=\"?(.*)\"?");
  QRegularExpressionMatch match;
  match=rx.match(Type);
  if(Type.contains("plain")) {
      ViewContentToReply=sub_utf;
      ViewType=match.captured(1);
    }
}

void emlBrower::alterDecode(QString src,QString boundary){
  QStringList srcpart;
 // qDebug()<<"alterbd:"<<"--"+boundary;
  if(boundary.size()) srcpart=src.split("--"+boundary); //根据段名切分
  else srcpart<<src;
  QRegularExpression rxContent_Type("Content-Type:\\s*(.*\r?\n?\\s*charset=.*)\r\n");
  QRegularExpression rxContent_Transfer_Encoding("Content-Transfer-Encoding:\\s*(.*)\r\n");
  QRegularExpressionMatch matchType,matchEncoding;
  for(int i=0;i<srcpart.size();i++){
      QString src=srcpart.at(i).toLatin1();
  //    qDebug()<<i<<"src :"<<src;
      QByteArray content;
      matchType=rxContent_Type.match(src);
      matchEncoding=rxContent_Transfer_Encoding.match(src);
      if(matchType.hasMatch()){
           QStringList srclist = src.split("\r\n\r\n");//以空行划分
           src.remove(0,srclist.at(0).size()+4);//去掉Content编码信息段
           if(matchEncoding.captured(1).toUpper().contains("BASE64")) content=QByteArray::fromBase64(src.toLatin1());
           else if(matchEncoding.captured(1).toUpper().contains("QUOTED")) content=eml->DecodequotedPrintable(src.toLatin1());
           else content=src.toLocal8Bit();
        }
//      qDebug()<<content<<matchType.captured(1);
      if(matchType.captured(0).contains("html")) {
        view->setContent(content,matchType.captured(1).remove("\"")); //显示html内容
        setView=true;
      }
      else if(!setView) view->setContent(content,matchType.captured(1).remove("\""));
      if(matchType.captured(0).contains("plain")){
        ViewContentToReply=content; //回复纯文本
        QRegularExpression rx("charset=\"?(.*)\"?");
        QRegularExpressionMatch match;
        match=rx.match(matchType.captured(1));
        ViewType=match.captured(1);
        }
    }
}

void emlBrower::relatedDecode(QString src, QString boundary)
{
  //剥掉related壳
  QStringList srcpart;
  if(boundary.size()) srcpart=src.split("--"+boundary); //根据段名切分
  else srcpart<<src;
  QRegularExpression rxContent_Type("Content-Type:\\s*((.*?\r?\n?\\s*(charset=.*)?)(\\s*boundary=\"(.*)\")?)\r\n");
  QRegularExpression rxContent_Transfer_Encoding("Content-Transfer-Encoding:\\s*(.*)\r\n");
  QRegularExpressionMatch matchType,matchEncoding;
  for(int i=0;i<srcpart.size();i++){
      QString src=srcpart.at(i).toLatin1();
      QStringList srclist = src.split("\r\n\r\n");//以空行划分
      matchType=rxContent_Type.match(srclist.at(0)+"\r\n");
      matchEncoding=rxContent_Transfer_Encoding.match(srclist.at(0)+"\r\n");
      src.remove(0,srclist.at(0).size());//去掉Content编码信息段
      if(matchType.hasMatch()){
          distribute(src,matchType.captured(2).remove("\""),matchType.captured(5).remove("\""),matchEncoding.captured(1));
        }
    }
}

void emlBrower::mixedDecode(QString src, QString boundary)
{
  QStringList srcpart;
  if(boundary.size()) srcpart=src.split("--"+boundary); //根据段名切分
  else srcpart<<src;
  QRegularExpression rxContent_Type("Content-Type:\\s*(.*)");
  QRegularExpression rxContent_attachment("Content-Disposition:\\s*attachment;\\s*filename=\"(.*)\"");
  QRegularExpression rxContent_Transfer_Encoding("Content-Transfer-Encoding:\\s*(.*)");
  QRegularExpressionMatch match,matchType,matchEncoding,match_attach;

  for(int i=0;i<srcpart.size();i++){
      QString src=srcpart.at(i).toLatin1();
      QStringList srclist = src.split("\r\n\r\n");//以空行划分
      QStringList part = srclist.at(0).split("\r\n");
      QRegularExpression rxSpace("\\s");
      for(int j=0;j<part.size();){
          if((j+1)<part.size()){
              if(rxSpace.match(part.at(j+1).left(1)).hasMatch()){
                  part[i].append(part.at(j+1)); //\r作为切分标志，注意，在QRegularExpression中"."不能匹配\n
                  part.removeAt(j+1);
                  continue; //此处无需j++，因为part.size()--
                }
            }
          j++;
        }
      QString Type,Encoding,attachmentname;
      for(int j=0;j<part.size();j++){
          matchType=rxContent_Type.match(part.at(j));
          if(matchType.hasMatch()) Type=matchType.captured(1);
          matchEncoding=rxContent_Transfer_Encoding.match(part.at(j));
          if(matchEncoding.hasMatch()) Encoding=matchEncoding.captured(1);
          match_attach=rxContent_attachment.match(part.at(j));
          if(match_attach.hasMatch()) attachmentname=match_attach.captured(1);
        }
      src.remove(0,srclist.at(0).size()+4);//去掉Content编码信息段 +去掉的\r\n\r\n
      if(Type.size()){
 //         qDebug()<<"Mix: "<<Type<<Encoding<<attachmentname;
          QRegularExpression b("boundary=\"(.*)\"\\s?");
          QRegularExpressionMatch match;
          match=b.match(Type);
          QString bd;
          if(match.hasMatch()){
              Type.remove(match.captured(0));
              bd=match.captured(1);
            }
   //       qDebug()<<"boundary: "<<bd;
          if(Type.contains("application/octet-stream")){
          //处理附件
             attachDecode(src,Encoding,attachmentname);
          }
          else if(Type.contains("application/rtf")){
             attachDecode(src,Encoding,"rtf.rtf");
            }
          else distribute(src,Type.remove("\""),bd.remove("\""),Encoding);
        }
//      if(matchType.hasMatch()){
//          qDebug()<<src;
//          qDebug()<<matchType.captured(4).remove("\"");
//          qDebug()<<matchEncoding.captured(1);
    }
}

void emlBrower::distribute(QString src, QString Type, QString boundary, QString Encoding)
{
  if(Type.contains("text")){
  //    qDebug()<<"base!";
      baseDecode(src,Type,Encoding);
    }
  else if(Type.contains("multipart/alternative")){
  //    qDebug()<<"alter!";
  //    qDebug()<<src;
      alterDecode(src,boundary);
    }
  else if(Type.contains("multipart/related")){
  //    qDebug()<<"related!";
      relatedDecode(src,boundary);
    }
  else if(Type.contains("multipart/mixed")){
  //    qDebug()<<"mixed!";
      mixedDecode(src,boundary);
    }
}

void emlBrower::attachDecode(QString &src, QString Encoding, QString filename)
{
      //如果是附件，则保存至文件
      QByteArray content;
      //QTextCodec * codec= QTextCodec::codecForName("gb18030");//matchType.captured(4).remove("\"").toLatin1());
      if(Encoding.toUpper().contains("BASE64")) content=QByteArray::fromBase64(src.toLatin1());
      else if(Encoding.toUpper().contains("QUOTED")) content=eml->DecodequotedPrintable(src.toLatin1());
      else content=src.toLocal8Bit();
      QFile file(eml->DecodeHeaderText(filename));
      if(file.open(QFile::WriteOnly)){
          file.write(content);
          file.close();
        }
      AttachFile newAttach;
      newAttach.Filecontent=content;
      newAttach.Filename=eml->DecodeHeaderText(filename);
      AttachList<<newAttach;
      QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->listView->model());
      root->appendRow(new QStandardItem(eml->DecodeHeaderText(filename)));
}


emlBrower::~emlBrower()
{
  this->close();
  delete this->eml;
  delete this->view;
  delete ui;
}

void emlBrower::on_pushButton_clicked()
{
    if(ui->listView->currentIndex().row()>=0){
        QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->listView->model());
        QDesktopServices::openUrl(QUrl(root->item(ui->listView->currentIndex().row())->text()));
      }
}

void emlBrower::on_listView_clicked(const QModelIndex &index)
{
  ui->pushButton->setEnabled(true);
  ui->pushButton_2->setEnabled(true);
}

void emlBrower::on_listView_doubleClicked(const QModelIndex &index)
{
  if(index.row()>=0){
      QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->listView->model());
      QTextCodec* codec=QTextCodec::codecForLocale();
      QDesktopServices::openUrl(QUrl(codec->toUnicode(root->item(index.row())->text().toLocal8Bit())));
    }
}

void emlBrower::on_pushButton_3_clicked()
{
  auto ret = QMessageBox::warning(0,QString::fromLocal8Bit("确认？"),QString::fromLocal8Bit("您确认要在服务器上删除该邮件？从客户端删除的邮件不会加入“已删除”，个别邮箱如需恢复请登录服务器操作"),QMessageBox::Ok|QMessageBox::Cancel);
  if(ret==QMessageBox::Ok)  {
      emit deleteMail(eml->getFolderindex(),eml->getHeaderindex());
      ui->pushButton_3->setText(QString::fromLocal8Bit("已标记删除"));
      ui->pushButton_3->setEnabled(false);
    }
}

void emlBrower::on_pushButton_4_clicked()
{
  emit reply(eml->getAccount(),eml->getFrom(),"Re_"+eml->getSubject(),
             QString::fromLocal8Bit("\r\n\r\n\r\n")+
             QString::fromLocal8Bit("-------- 原始邮件 --------\r\n")+
             QString::fromLocal8Bit("在 ")+
             eml->getDate()+
             " "+
             eml->getFrom()+
             QString::fromLocal8Bit(" 写道:\r\n")+
             ViewContentToReply
             );
  this->setWindowState(Qt::WindowMinimized);
}

void emlBrower::on_pushButton_5_clicked()
{
  emit reply(eml->getAccount(),"",eml->getSubject(),
             ViewContentToReply
             );
  this->setWindowState(Qt::WindowMinimized);
}

void emlBrower::on_pushButton_6_clicked()
{
  QFileDialog *fileDialog = new QFileDialog(this);
  fileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件夹"));
  fileDialog->setDirectory(".");
  QString name = eml->getSubject()+".eml";
  fileDialog->selectFile(name);
  fileDialog->setLabelText(QFileDialog::Accept,QString::fromLocal8Bit("保存文件"));
  if (fileDialog->exec() == QDialog::Accepted) {
      QString path = fileDialog->selectedFiles().at(0);
      QFile file(path);
      if(file.open(QIODevice::WriteOnly)){
          QTextStream out(&file);
          out<<eml->getHeader();
          out<<eml->getBody();
          file.close();
        }
      QMessageBox::information(0,QString::fromLocal8Bit("保存成功！"),QString::fromLocal8Bit("保存成功！"),QMessageBox::Ok);
  }
}

void emlBrower::on_pushButton_2_clicked()
{
  qint32 index=ui->listView->currentIndex().row();
  if(index>=0){
      QFileDialog *fileDialog = new QFileDialog(this);
      fileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件夹"));
      fileDialog->setDirectory(".");
      fileDialog->selectFile(AttachList.at(index).Filename);
      fileDialog->setLabelText(QFileDialog::Accept,QString::fromLocal8Bit("保存文件"));
      if (fileDialog->exec() == QDialog::Accepted) {
          QString path = fileDialog->selectedFiles().at(0);
                QFile file(path);
                if(file.open(QFile::WriteOnly)){
                    file.write(AttachList.at(index).Filecontent);
                    file.close();
                  }
          QMessageBox::information(0,QString::fromLocal8Bit("保存成功！"),
                                   QString::fromLocal8Bit("保存成功！"),QMessageBox::Ok);
      }
    }
}
