#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QVector>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "localhost"
#define DATABASE_PATH       "./db/"
#define DATABASE_NAME       "Modules.sqlite3"

// Первая колонка содержит Autoincrement ID

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();        // Открытие базы данных
    bool restoreDataBase();     // Восстановление базы данных
    void closeDataBase();       // Закрытие базы данных
    bool createTable(const QString &tableName, const QVariantList& data);         // Создание базы таблицы в базе данных

public slots:
    bool inserIntoTable(const QString &tableName, const QStringList &fields, const QStringList &data);      // Добавление записей в таблицу
    bool inserIntoTable(const QString &fname, const QString &sname, const QString &nik);
    QVector<QStringList> getModuleData(const int moduleId);
    bool removeRecord(const QString& tableName, const int id); // Удаление записи из таблицы по её id
};

#endif // DATABASE_H
