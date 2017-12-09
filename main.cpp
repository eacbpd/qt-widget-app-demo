//关于求职者在参加面试或者签订劳动合同时，应向用人单位披露哪些个人信息，法律只作了概括性规定，
//即《劳动合同法》第8条规定：“用人单位有权了解劳动者与劳动合同直接相关的基本情况，劳动者应当如实说明”
//“与劳动合同直接相关”的信息，指的是单位享有知情权,但主要是指与劳动者任职资格匹配的信息。
//至于与招聘职位无直接关系的个人信息，如婚姻状况、生活经历、财产状况、嗜好、是否单亲家庭、
//与劳动能力无关的生理缺陷等，应属于隐私权所保护的范围。
//求职者没有披露义务，用人单位也不能强求，否则就可能构成对劳动者的就业歧视。

#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("eacbpd");
        database.setPassword("123456");
        qDebug()<<"create new datebase"<<QCoreApplication::applicationDirPath();
    }

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
        QSqlQuery sql_query;

        QString exist_sql = "select * from sqlite_master where name='student'";
        sql_query.prepare(exist_sql);
        sql_query.exec();
        if(sql_query.size()==0)
        {
            QString create_sql = "create table student (id int primary key, name varchar(30), age int)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
            {
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            }
            else
            {
                qDebug() << "Table created!";
            }
        }
        else
        {
            qDebug()<< "Table Exist!";
        }


        QString insert_sql = "insert into student values (?, ?, ?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(1);
        sql_query.addBindValue("Wang");
        sql_query.addBindValue(25);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted Wang!";
        }
        if(!sql_query.exec("INSERT INTO student VALUES(2, \"Li\", 23)"))
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted Li!";
        }
    }

    QSqlQuery sql_query;
    QString sql_select="select * from student";
    sql_query.prepare(sql_select);
    sql_query.exec();
    while(sql_query.next())
    {
        qDebug()<<sql_query.value(0)<<' '<<sql_query.value(1)<<' '<<sql_query.value(2);
    }

    database.close();

    MainWindow w;
    w.show();

    return a.exec();
}
