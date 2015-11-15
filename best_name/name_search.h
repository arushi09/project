#ifndef NAME_SEARCH_H
#define NAME_SEARCH_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QtSql/QtSql>

#include <QMessageBox>


namespace Ui {
class Name_search;
}

class Name_search : public QMainWindow
{
    Q_OBJECT

    void readCSV(void);
public:
    QSqlDatabase db;
    explicit Name_search(QWidget *parent = 0);
    ~Name_search();

private:
    Ui::Name_search *ui;

public slots:
    void searchClick_slot();
    void plotClick_slot();
};

#endif // NAME_SEARCH_H
