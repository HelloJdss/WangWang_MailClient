#include "emlbrower.h"
#include "ui_emlbrower.h"

emlBrower::emlBrower(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::emlBrower)
{
  ui->setupUi(this);
}

emlBrower::~emlBrower()
{
  delete ui;
}
