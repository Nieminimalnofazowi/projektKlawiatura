#ifndef TYPEDTEXTEDIT_H
#define TYPEDTEXTEDIT_H

#include <QTextEdit>

class QKeyEvent;

class TypedTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TypedTextEdit(QWidget *parent = 0);

signals:
    void textChanged(bool isBackspace);

protected:
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void userTypedWrongCharacter();
    void userTypedCorrectCharacter();

private:
    bool wrongCharater;
};

#endif // TYPEDTEXTEDIT_H
