#include "caction.h"

CAction::CAction(QString text, QString jsAction, QAction *qaction, int x, int y) :    QObject() {
    this->_text = text;
    this->_jsAction = jsAction;
    this->qaction = qaction;
    this->x = x;
    this->y = y;
}

void CAction::triggered() {
    emit(triggeredExt(this->_text, this->_jsAction));
}

