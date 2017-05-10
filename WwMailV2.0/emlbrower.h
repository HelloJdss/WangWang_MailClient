#ifndef EMLBROWER_H
#define EMLBROWER_H

#include <QWidget>

namespace Ui {
  class emlBrower;
}

class emlBrower : public QWidget
{
  Q_OBJECT

public:
  explicit emlBrower(QWidget *parent = 0);
  ~emlBrower();

private:
  Ui::emlBrower *ui;
};

#endif // EMLBROWER_H
