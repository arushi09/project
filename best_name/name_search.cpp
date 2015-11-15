#include "name_search.h"
#include "ui_name_search.h"

Name_search::Name_search(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Name_search)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);

   ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Count"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Rank"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Year"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Gender"));
    QObject::connect(ui->pushButton_search,SIGNAL(clicked()),this,SLOT(searchClick_slot()));
     QObject::connect(ui->pushButton_plot,SIGNAL(clicked()),this,SLOT(plotClick_slot()));

     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("namedatabase.sqlite3");
     if(!db.open())
     {
         QMessageBox::critical(0, qApp->tr("Cannot open database"),
                            qApp->tr("Unable to establish a database connection.\n"
                                     "This example needs SQLite support. Please read "
                                     "the Qt SQL driver documentation for information how "
                                     "to build it.\n\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

     }
     //this->readCSV();
}

Name_search::~Name_search()
{
    delete ui;
}

void Name_search::searchClick_slot()
{
 QSqlQuery query(db);
    int sqyear;
    int sqlimit;
    sqlimit=ui->spinBox_top->value();
        sqyear=ui->dateEdit_year->date().year();
        sqyear++;


        if(ui->checkBox_male->isChecked() && ui->checkBox_female->isChecked())
        {
            query.prepare("SELECT * FROM names  where year=:year order by count desc");

        }else if (!ui->checkBox_male->isChecked() && !ui->checkBox_female->isChecked()){
            query.prepare("SELECT * FROM names  where year=:year order by count desc");

        }else if(!ui->checkBox_female->isChecked())
        {
            query.prepare("SELECT * FROM names  where year=:year and gen=\"m\" order by count desc");

        }
        else if(!ui->checkBox_male->isChecked())
        {
            query.prepare("SELECT * FROM names  where year=:year and gen=\"f\" order by count desc");

        }


        query.bindValue(":year",sqyear);
        if(!query.exec()){
           qDebug() << "does not execute";
        }

               ui->tableWidget->setRowCount(sqlimit);


              ui->tableWidget->setColumnCount(5);
               int m=0;
               while(query.next()) {
                   for(int i = 0; i <5; i++) {
                        QString str = query.value(i).toString();
                        QTableWidgetItem *item = new QTableWidgetItem();
                        item->setText(str);
                        if(i==3){
                            item->setText(QString::number(sqyear-1));
                        }else if(i==4)
                        {
                           if( item->text()=="f")
                               item->setText("Female");
                           else if(item->text()=="m"){
                               item->setText("Male");
                           }
                        }
                        ui->tableWidget->setItem(m,i,item);
                   }
                   m++;
               }
               ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
               ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Count"));
               ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Rank"));
               ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Year"));
               ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Gender"));
}

/*
void Name_search::readCSV(void)
{
QSqlDatabase db;
db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("namedatabase.sqlite3");


QString fileName ;
    int year =1944;
    if(db.open())
    {

        QSqlQuery query(db);

        while(year<2014){
    fileName.sprintf("names/female_cy%d_top.csv",year);
    year++;
    QFile file (fileName);

    if (file.open(QIODevice::ReadOnly)) {
        QString line = file.readLine(500);
        while(!file.atEnd()){
        QString line = file.readLine(500);
        line.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        line.remove( QRegExp("\"") ); //remove all ocurrences of CR (Carriage Return)
        line.remove( QRegExp("\n") ); //remove all ocurrences of CR (Carriage Return)
        line.remove( QRegExp("=") ); //remove all ocurrences of CR (Carriage Return)

        QStringList wordlist= line.split(',');
        QListIterator<QString> itr(wordlist);
        QString sqname,sqgen;
        int sqcount,sqpoj,sqyear;
        sqname=itr.next();
        sqcount =itr.next().toInt();
        sqpoj=itr.next().toInt();
        sqyear=year;
        sqgen="f";

                  query.prepare("INSERT INTO names (name, count, poj,year,gen) "
                                    "VALUES (:name, :count, :poj,:year,:gen)");
                      query.bindValue(":name",sqname);
                      query.bindValue(":count",sqcount);
                      query.bindValue(":poj", sqpoj);
                      query.bindValue(":year",sqyear);
                      query.bindValue(":gen", sqgen);
                      if(!query.exec()){
                          qDebug() << "does not execute";
                      }
//                      QSqlRecord record = db.record("names");
//                            int fieldcount = record.count();
//                            fieldcount=fieldcount+1;

        }
    }
    file.close();

   }

year=1944;
        while(year<2014){
    fileName.sprintf("names/male_cy%d_top.csv",year);
    year++;
    QFile file (fileName);

    if (file.open(QIODevice::ReadOnly)) {
        QString line = file.readLine(500);
        while(!file.atEnd()){
        QString line = file.readLine(500);
        line.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        line.remove( QRegExp("\"") ); //remove all ocurrences of CR (Carriage Return)
        line.remove( QRegExp("\n") ); //remove all ocurrences of CR (Carriage Return)
        line.remove( QRegExp("=") ); //remove all ocurrences of CR (Carriage Return)

        QStringList wordlist= line.split(',');
        QListIterator<QString> itr(wordlist);
        QString sqname,sqgen;
        int sqcount,sqpoj,sqyear;
        sqname=itr.next();
        sqcount =itr.next().toInt();
        sqpoj=itr.next().toInt();
        sqyear=year;
        sqgen="m";

                  query.prepare("INSERT INTO names (name, count, poj,year,gen) "
                                    "VALUES (:name, :count, :poj,:year,:gen)");
                      query.bindValue(":name",sqname);
                      query.bindValue(":count",sqcount);
                      query.bindValue(":poj", sqpoj);
                      query.bindValue(":year",sqyear);
                      query.bindValue(":gen", sqgen);
                      if(!query.exec()){
                          qDebug() << "does not execute";
                      }
//                      QSqlRecord record = db.record("names");
//                            int fieldcount = record.count();
//                            fieldcount=fieldcount+1;

        }
    }
    file.close();

   }


    }
    db.close();


}

*/





void Name_search::plotClick_slot()
{
int i,ymax,xyear;
QString sqlname;
QString sqlgen;

QVariant test;
QSqlQuery query(db);
QVector<double> x(101), y(101); // initialize with entries 0..100
    xyear=ui->dateEdit_year_plot->date().year();
sqlname=ui->lineEdit_name_plot->text().replace(" ","").toUpper();
if(ui->checkBox_male_plot->isChecked() && ui->checkBox_female_plot->isChecked())
{
    query.prepare("select count,year from names where name = :name and year>=:year");

}else if (!ui->checkBox_male_plot->isChecked() && !ui->checkBox_female_plot->isChecked()){
    query.prepare("select count,year from names where name = :name and year>=:year");

}else if(!ui->checkBox_female_plot->isChecked())
{
    query.prepare("select count,year from names where name = :name and year>=:year and gen=\"m\"");

}
else if(!ui->checkBox_male_plot->isChecked())
{
    query.prepare("select count,year from names where name = :name and year>=:year and gen=\"f\"");


}

        query.bindValue(":year",xyear);
    query.bindValue(":name",sqlname);
    query.bindValue(":gen",sqlgen);

        if(!query.exec()){
            //invalid entry
        }
  // query.exec( "select count,year from names where name = \"HELEN\" and year>=2000 and gen");
   //query.exec( "create table test(id int primary key, name varchar(20), city int, country int)");
  i=0;
  ymax=0;
   while(query.next())
           {
               y[i]=query.value(0).toInt();
          if(y[i]>ymax)
              ymax=y[i];
               x[i]=query.value(1).toInt();
i++;
   //            QLabel *label = new QLabel(QString());
   //            QCheckBox *chkbox = new QCheckBox;

   //            Ui::MainWindow *ui;

   //            ui->gridLayout->addWidget(label,0,0);
   //            ui->gridLayout->addWidget(chkbox,0,1);
           }
   QSqlRecord rec=query.record();
   if(rec.isEmpty())
   {
       //meg not enough data
   }

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Year");
    ui->customPlot->yAxis->setLabel("Popularity");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(xyear, 2013);
    ymax=ymax+(ymax*0.1);

    ui->customPlot->yAxis->setRange(0, ymax);
    ui->customPlot->replot();
}
