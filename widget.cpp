#include "widget.h"
#include "./ui_widget.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegExpValidator>
#include <QRegularExpressionMatch>



Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget)
{
  ui->setupUi(this);
  setWindowTitle("QRegularExpression tester");
  connect(ui->patternLE, &QLineEdit::editingFinished,this,&Widget::test);
  connect(ui->subjectLE, &QLineEdit::editingFinished,this,&Widget::test);
  connect(ui->pushButton, &QPushButton::pressed,this,&Widget::test);
  test();
}

Widget::~Widget()
{
  delete ui;
}

void Widget::test()
{
  ui->uitvoerPTE->clear();
  ui->errorLE->clear();
  QRegularExpression rea(ui->patternLE->text());
  QRegExpValidator va;
  if(rea.isValid())
    {
      QRegularExpressionMatch matcha = rea.match(ui->subjectLE->text());
      qDebug()<< matcha.hasMatch()<<matcha.hasPartialMatch();
      if (matcha.hasMatch())
        {
          int var = rea.captureCount();
          QStringList names = rea.namedCaptureGroups();
          qDebug()<<names<<var;
          for (;var>0;var--) {
              qDebug()<<var<<names.at(var)<< matcha.captured(names.at(var));
              ui->uitvoerPTE->appendPlainText(
                    names.at(var)+" : "+ matcha.captured(names.at(var)));
            }
        }
    }
  else
    {
      qDebug()<< rea.errorString()<<rea.patternErrorOffset();
      ui->errorLE->setText(rea.errorString());
  }
}
