#pragma once
#include <QTextEdit>
#include <QString>
#include <QTextStream>
#include <QFile>


class Debuger{
public:
    Debuger(QTextEdit* textEdit, QFile* file) : textEdit_(textEdit){
        if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
            fileStream_ = new QTextStream(file);
        }
    }

    Debuger(QTextEdit* textEdit) : textEdit_(textEdit){}

    ~Debuger(){
        delete fileStream_;
    }

    void start(QString title, QString info)
    {
        title_ = title;
        lastText = info;
        setColor(Qt::blue);
        insert("==START==" + info);
    }

    void end(QString info = "")
    {
        setColor(Qt::blue);
        insert("--ENDED--" + info);
        lastText = "";
        insertIntoTextBoxAndFile("");
    }

    void insert(QString info)
    {
        insertIntoTextBoxAndFile(title_ + ":" + info);
        setColor(Qt::black);
    }


    void insertError(QString info)
    {
        setColor(Qt::red);
        insert("[ERROR]" + info);
    }

private:
    void insertIntoTextBoxAndFile(QString text){
        insertIntoTextBox(text);
        insertIntoFileStream(text);
    }

    void insertIntoTextBox(QString text){
        if(textEdit_)
            textEdit_->append(text);
    }

    void insertIntoFileStream(QString text){
        if(fileStream_)
            fileStream_->operator<<(text + "\n");
    }

    void setColor(const QColor& color){
        if(textEdit_)
            textEdit_->setTextColor(color);
    }

private:
    QTextEdit* textEdit_;
    QTextStream* fileStream_;

    QString title_ = "";
    QString lastText = "";
};


