#include "qdynamicbutton.h"


QDynamicButton::QDynamicButton(QWidget *parent,int n_,int m_) :
    QRadioButton(parent),
    n(n_),
    m(m_)
{

}

QDynamicButton::~QDynamicButton()
{

}

int QDynamicButton::getM() const
{
    return this->m;
}

int QDynamicButton::getN() const
{
    return this->n;
}
