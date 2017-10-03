#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    //if(!QFile(DATABASE_PATH DATABASE_NAME).exists()){
        this->restoreDataBase();
    //} else {
    //    this->openDataBase();
    //}
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    bool status = true;
    // Если база данных открылась ...
    if(this->openDataBase()){
        // Производим восстановление базы данных
        status = status && (bool) this->createTable(
            "modules", {
                "module_id INTEGER PRIMARY KEY AUTOINCREMENT, ",
                "type VARCHAR(255) NOT NULL,",
                "name VARCHAR(255) NOT NULL,",
                "price VARCHAR(255) NULL"
            }
        );
        status = status && (bool) this->createTable(
            "module_parts", {
                "module_part_id INTEGER PRIMARY KEY AUTOINCREMENT, ",
                "module_id INTEGER,",
                "type_id VARCHAR(255) NOT NULL,",
                "name VARCHAR(255) NOT NULL,",
                "description TEXT NULL",
                "price VARCHAR(255) NULL"
            }
        );

    } else {
        qDebug() << "Не удалось восстановить базу данных";
        status = false;
    }
    return status;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_PATH DATABASE_NAME);

    return db.open();
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable(const QString& tableName, const QVariantList& data)
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    QString q;

    q += "CREATE TABLE IF NOT EXISTS " + tableName + " (";

    for(const auto& x: data)
        q += x.toString();
    q += ")";

    if(!query.exec(q)){
        qDebug() << "DataBase: error of create " << tableName;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QString& tableName, const QStringList& fields, const QStringList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */

    QStringList params;
    for(const auto& x: fields)
        params.push_back(QString(":%1").arg(x));

    query.prepare(QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName, fields.join(", "), params.join(", ")));
    for(const auto& x: fields)
        query.bindValue(QString(":%1").arg(x), x);

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << tableName;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Второй метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QString &fname, const QString &sname, const QString &nik)
{
    QVariantList data;
    data.append(fname);
    data.append(sname);
    data.append(nik);

    return false;
    //return inserIntoTable(data);
}

QVector<QStringList> DataBase::getModuleData(const int moduleId)
{
    QSqlQuery query;

    QVector<QStringList> data;
    query.prepare("SELECT * FROM module_parts WHERE module_id = :ID");
    query.bindValue(":ID", moduleId);

    while (query.next())
    {
        QStringList row;
        for(int i = 0, cnt = query.record().count(); i < cnt; ++i)
            row << query.record().value(i).toString();
        data << row;
    }

    return data;
}

/* Метод для удаления записи из таблицы
 * */
bool DataBase::removeRecord(const QString& tableName, const int id)
{
    // Удаление строки из базы данных будет производитсья с помощью SQL-запроса
    QSqlQuery query;

    // Удаление производим по id записи, который передается в качестве аргумента функции
    query.prepare("DELETE FROM " + tableName + " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    // Выполняем удаление
    if(!query.exec()){
        qDebug() << "error delete row " << tableName;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
