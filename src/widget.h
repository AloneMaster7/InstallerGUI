#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QFrame>
#include <QLinkedList>
#include <QPushButton>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QVBoxLayout* l;
    QList<QFrame*> steps;
    int current;
    QPushButton* Agreement;
    QProgressBar* pbar;
    QTimer* t;
    QPushButton* finish;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::Widget *ui;
    void firstStep();
    void secondStep();
    void thirdStep();
    void fourthStep();
private slots:
    void nextStep();
    void prevStep();
    void openFileDialog();
    void disEn(bool s=false);
    void installing();
    void aboutToClose();
};
#endif // WIDGET_H
