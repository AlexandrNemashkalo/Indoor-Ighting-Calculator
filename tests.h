#ifndef TESTS_H
#define TESTS_H

#include "cassert"
#include "iostream"
#include "lamp.h"
#include <QRandomGenerator>
#include "float.h"
#include "matrix.h"
namespace Random
{
float realNumber(float from = FLT_MIN/2, float to = FLT_MAX/2) ;
}

void assertDefaultConstructorLamp(const Lamp& lamp);
void assertInitConstructorLamp(const Lamp& lamp);
void assertCopyConstructorLamp(const Lamp& first, const Lamp& second);
void assertStability(Lamp& object);

void assertCopyConstructorMatrix(const Matrix& first, const Matrix& second);
void assertInitConstructorMatrix(const Matrix& matrix);
void assertGetMatrix(const Matrix& matrix);



void startTests();

#endif // TESTS_H
