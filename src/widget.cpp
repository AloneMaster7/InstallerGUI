#include "widget.h"
#include "ui_widget.h"
#include <QLayout>
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(600,400);
    this->setWindowTitle("Setup Progress");
    this->setStyleSheet("QWidget {background-color:black;background-image:url(b.jpg);}"
                        "QLabel {color:rgb(220,220,220);}"
                        "QPushButton {color:rgb(220,220,220);}"
                        "QPushButton:pressed {color:red}"
                        "QLineEdit {color:rgb(220,220,220);}"
                        "QCheckBox {color:rgb(220,220,220);}"
                        "QProgressBar {color:rgb(220,220,220);}"
                        "QPushButton:disabled {color:rgb(0,0,0)}");
    this->current = 0;
    this->l = new QVBoxLayout;
    this->setLayout(this->l);
    this->firstStep();
    this->secondStep();
    this->thirdStep();
    this->fourthStep();
    foreach(QWidget* w,this->steps){
        if(w != this->steps.begin().i->t())
            w->setVisible(false);
        this->l->addWidget(w);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    this->resize(600,400);
}

void Widget::firstStep()
{
    QVBoxLayout* l = new QVBoxLayout;
    QFrame* f = new QFrame;
    f->setLayout(l);
    f->setStyleSheet("QLabel {color:rgb(220,220,220);}"
                     "QPushButton {color:rgb(220,220,220);}"
                     "QPushButton:pressed {color:red;}"
                     "QLineEdit {color:rgb(220,220,220);}");

    QLabel* lb1 = new QLabel("<center><h3>Hello , Welcome to Setup</h3><center>"
                             "<h5>I am glad to see that you want to "
                             "install my software</h5>");
    //lb1->setAlignment(Qt::AlignTop);
    l->addWidget(lb1);

    QVBoxLayout* lv1 = new QVBoxLayout;
    QLabel* lb2 = new QLabel("<p><h4>This program just shows you a cool"
                             " GUI, does not anything...<br/>"
                             "watch it and enjoy it ;)"
                             "<br/><br/><br/><br/><br/><br/><br/><br/><br/></p></h4>");
    lb2->setAlignment(Qt::AlignTop);lv1->setContentsMargins(0,0,0,10);
    lv1->addWidget(lb2);
    l->addLayout(lv1);
    l->addSpacing(70);

    QPushButton* pb1 = new QPushButton("Next >");
    QPushButton* pb2 = new QPushButton("X Cancel");
    QHBoxLayout* hl1 = new QHBoxLayout;
    hl1->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    hl1->addWidget(pb2);
    hl1->addWidget(pb1);
    l->addLayout(hl1);
    QObject::connect(pb2,SIGNAL(clicked()),this,SLOT(aboutToClose()));
    QObject::connect(pb1,SIGNAL(clicked()),this,SLOT(nextStep()));

    this->steps<<f;
}

void Widget::secondStep()
{
    QVBoxLayout* l = new QVBoxLayout;
    QFrame* f = new QFrame;
    f->setLayout(l);
    f->setStyleSheet("QLabel {color:rgb(220,220,220);}"
                     "QPushButton {color:rgb(220,220,220);}"
                     "QPushButton:pressed {color:red}"
                     "QLineEdit {color:rgb(220,220,220);}"
                     "QTextEdit {color:rgb(220,220,220);}"
                     "QCheckBox {color:rgb(220,220,220);}"
                     "QPushButton:disabled {color:rgb(0,0,0)}");

    QLabel* lb1 = new QLabel("<center><h3>Read And Agree Our Privacy</h3><center>");
    l->addWidget(lb1);

    QVBoxLayout* vl1 = new QVBoxLayout;
    QTextEdit* te = new QTextEdit;
    te->setReadOnly(true);
    te->setText("<center><h3>LICENSE AGREEMENT</h3></center><br><br>"
                "By installing and using this software , I accept all policies of "
                "programmer and I promise that I <b>DO NOT</b> publish this software"
                " without permission.<br>"
                "if you agree with this , then click Next button which is in the"
                " bottom of window. and remember that , always read license agreement"
                "before installing anything ;)");
    vl1->addWidget(te);
    QCheckBox* chb1 = new QCheckBox("I have read and agree with license agreement");
    vl1->addWidget(chb1);
    l->addLayout(vl1);

    this->Agreement = new QPushButton("Next >");
    QPushButton* pb2 = new QPushButton("< Back");
    QHBoxLayout* hl2 = new QHBoxLayout;
    hl2->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    hl2->addWidget(pb2);
    hl2->addWidget(this->Agreement);
    l->addLayout(hl2);
    QObject::connect(pb2,SIGNAL(clicked()),this,SLOT(prevStep()));
    QObject::connect(this->Agreement,SIGNAL(clicked()),this,SLOT(nextStep()));
    this->Agreement->setDisabled(true);
    QObject::connect(chb1,SIGNAL(clicked(bool)),this,SLOT(disEn(bool)));

    this->steps<<f;
}

void Widget::thirdStep()
{
    QVBoxLayout* l = new QVBoxLayout;
    QFrame* f = new QFrame;
    f->setLayout(l);
    f->setStyleSheet("QLabel {color:rgb(220,220,220);margin-top:20px}"
                     "QPushButton {color:rgb(220,220,220);}"
                     "QPushButton:pressed {color:red}"
                     "QLineEdit {color:rgb(220,220,220);}"
                     "QCheckBox {color:rgb(220,220,220);"
                     "margin-left: 50px;margin-top: 20px}");

    QLabel* lb1 = new QLabel("<center><h3>Choose Path To Install</h3><center>");
    l->addWidget(lb1);

    QHBoxLayout* hl1 = new QHBoxLayout;
    QLineEdit* le = new QLineEdit(QDir::currentPath());
    hl1->addWidget(le);
    QPushButton* pb3 = new QPushButton("Browse");
    QFileDialog* fd = new QFileDialog;
    fd->setFileMode(QFileDialog::Directory);
    QObject::connect(pb3,SIGNAL(clicked()),fd,
                     SLOT(show()));
    QObject::connect(fd,SIGNAL(fileSelected(const QString&)),le,
                     SLOT(setText(const QString &)));
    hl1->addWidget(pb3);
    l->addLayout(hl1);

    QFormLayout* fl1 = new QFormLayout;
    fl1->addRow(new QLabel("Enable or Disable options that you want : "),
                new QLabel());
    fl1->addRow(new QCheckBox(" - Add Shortcut on Desktop"));
    fl1->addRow(new QCheckBox(" - Add Shortcut in Start Menu"));
    l->addLayout(fl1);

    l->addSpacing(100);
    QPushButton* pb1 = new QPushButton("Next >");
    QPushButton* pb2 = new QPushButton("< Back");
    QHBoxLayout* hl2 = new QHBoxLayout;
    hl2->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    hl2->addWidget(pb2);
    hl2->addWidget(pb1);
    l->addLayout(hl2);
    QObject::connect(pb2,SIGNAL(clicked()),this,SLOT(prevStep()));
    QObject::connect(pb1,SIGNAL(clicked()),this,SLOT(nextStep()));

    this->steps<<f;
}

void Widget::fourthStep()
{
    QVBoxLayout* l = new QVBoxLayout;
    QFrame* f = new QFrame;
    f->setLayout(l);
    f->setStyleSheet("QLabel {color:rgb(220,220,220);}"
                     "QPushButton {color:rgb(220,220,220);}"
                     "QPushButton:pressed {color:red}"
                     "QLineEdit {color:rgb(220,220,220);}"
                     "QCheckBox {color:rgb(220,220,220);}"
                     "QProgressBar {color:rgb(220,220,220);}"
                     "QPushButton:disabled {color:rgb(0,0,0)}");

    QLabel* lb1 = new QLabel("<center><h3>Please Wait While Installing...</h3><center>");
    l->addWidget(lb1);

    QVBoxLayout* vl1 = new QVBoxLayout;
    this->pbar = new QProgressBar;
    this->pbar->setRange(0,100);
    this->pbar->setValue(0);
    this->pbar->setFormat("%p% Completed");
    this->t = new QTimer;
    QObject::connect(this->t,SIGNAL(timeout()),this,SLOT(installing()));
    this->t->setInterval(500);
    vl1->addWidget(this->pbar);
    l->addLayout(vl1);
    l->addSpacing(170);

    this->finish = new QPushButton("Finish");
    this->finish->setDisabled(true);
    QPushButton* pb2 = new QPushButton("Cancel");
    QHBoxLayout* hl2 = new QHBoxLayout;
    hl2->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    hl2->addWidget(pb2);
    hl2->addWidget(this->finish);
    l->addLayout(hl2);
    QObject::connect(pb2,SIGNAL(clicked()),this,SLOT(aboutToClose()));
    QObject::connect(this->finish,SIGNAL(clicked()),this,SLOT(close()));

    this->steps<<f;
}

void Widget::nextStep()
{
    if(this->current == this->steps.count()-1)
        return;
    this->steps.at(this->current)->setVisible(false);
    this->steps.at(++this->current)->setVisible(true);
    if(this->current == 3)
        this->t->start();
}

void Widget::prevStep()
{
    if(this->current == 0)
        return;
    this->steps.at(this->current)->setVisible(false);
    this->steps.at(--this->current)->setVisible(true);
}

void Widget::openFileDialog()
{
    QFileDialog::getExistingDirectory(nullptr,"Choose Directory");
}

void Widget::disEn(bool s)
{
    if(this->Agreement->isEnabled())
        this->Agreement->setDisabled(true);
    else
        this->Agreement->setEnabled(true);
}

void Widget::installing()
{
    if(pbar->value() == pbar->maximum()){
        this->finish->setEnabled(true);
        return;
    }
    pbar->setValue(this->pbar->value()+(1+qrand()%10));
}

void Widget::aboutToClose()
{
    switch(QMessageBox::warning(this,"Really...?!","Are you sure to close?",
                                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)){
    case QMessageBox::Yes:
        this->close();
        break;
    case QMessageBox::No:
        return;
    }
}

