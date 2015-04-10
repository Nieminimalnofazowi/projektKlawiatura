#include "typedtextedit.h"
#include <QDebug>
#include <QKeyEvent>

TypedTextEdit::TypedTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    QObject* trueParent = parent->parent();
//    connect(parent->parent(), SIGNAL(wrongCharacterTyped), this, SLOT(userTypedWrongCharacter()));
//    connect(parent->parent(), SIGNAL(correctCharacterTyped), this, SLOT(userTypedCorrectCharacter()));
    wrongCharater = true;
}

void TypedTextEdit::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAccepted())
    {
        long int key = event->key();

        emit textChanged(key == Qt::Key_Backspace);
    }
    if(!this->wrongCharater)
    {
        QTextEdit::keyReleaseEvent(event);
    }
}

void TypedTextEdit::userTypedWrongCharacter()
{
    this->wrongCharater = true;
}

void TypedTextEdit::userTypedCorrectCharacter()
{
    this->wrongCharater = false;
}
