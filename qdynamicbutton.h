#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include <QRadioButton>

class QDynamicButton : public QRadioButton
{
    Q_OBJECT

public:
    QDynamicButton(QWidget *parent = 0,int n=0, int m=0);
    ~QDynamicButton();
    int getN() const;
    int getM() const;

private:
    int n;
    int m;


};

#endif // QDYNAMICBUTTON_H
