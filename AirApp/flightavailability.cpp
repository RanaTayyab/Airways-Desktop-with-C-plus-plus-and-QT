#include "flightavailability.h"
#include "ui_flightavailability.h"

FlightAvailability::FlightAvailability(QWidget *parent) :
    QMainWindow(parent),
    uid(new Ui::FlightAvailability)
{
    uid->setupUi(this);
    QString servername="RANATAYYABPC";
    QString dbn="AirlineSystem";

    db=QSqlDatabase::addDatabase("QODBC3");
    QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername).arg(dbn);
    db.setDatabaseName(dsn);

       db.setConnectOptions();
    db.open();

    if(!db.isOpen())
    {
        qDebug()<<"Error!!";

    }
    else
        qDebug()<<"ok";

    Filltable2();
}





void FlightAvailability::Filltable()
{

for(int i=0;i<row_counts;i++)
        uid->tableWidget->removeRow(i);


int num_rows,r,c;

//db.open();
QSqlQuery q;

if(!q.exec("select count(id) as num_rows from flightavailabilty  where origin='"+origin+"' and destination='" +destination+"' and dates='"+journeydate+"' "))qDebug()<<q.lastError().text();
q.first();

num_rows=q.value(0).toInt();

uid->tableWidget->setRowCount(num_rows);

if(!q.exec("select dates,flightname,departuretime,bcseats,xcseats,ecseats,price from flightavailabilty where origin='"+origin+"' and destination='" +destination+"' and dates='"+journeydate+"' " ))qDebug()<<q.lastError().text();



for(r=0,q.first();q.isValid();q.next(),++r){
    for(c=0;c<7;++c){

        uid->tableWidget->setItem(r,c,new QTableWidgetItem(q.value(c).toString()));
    }
}


}




void FlightAvailability::Filltable2()
{

int num_rows,r,c;


QSqlQuery q;

if(!q.exec("select count(id) as num_rows from flightavailabilty"))qDebug()<<q.lastError().text();
q.first();

num_rows=q.value(0).toInt();

uid->tableWidget->setRowCount(num_rows);

if(!q.exec("select dates,flightname,departuretime,bcseats,xcseats,ecseats,price from flightavailabilty " ))qDebug()<<q.lastError().text();

row_counts=num_rows;

for(r=0,q.first();q.isValid();q.next(),++r){
    for(c=0;c<7;++c){

        uid->tableWidget->setItem(r,c,new QTableWidgetItem(q.value(c).toString()));
    }
}


}



void FlightAvailability:: SetDetails(QString o,QString d,QString j){

origin=o;
destination=d;
journeydate=j;

}


void FlightAvailability:: CollectData()
{


SetDetails(uid->comboBox->currentText(),uid->comboBox_2->currentText(),uid->dateEdit->text());

}




FlightAvailability::~FlightAvailability()
{
    delete uid;
}

void FlightAvailability::on_pushButton_clicked()
{
    CollectData();
    qDebug()<<journeydate;
    if(origin=="Select"||destination=="Select")
    {
        Filltable2();
    }
    else
    Filltable();
}

void FlightAvailability::on_pushButton_2_clicked()
{

    QString temp= UserType::getUserType();

    if(temp=="Administrator")
    {


            MainMenus* cm=new MainMenus();
            this->hide();
             cm->show();




    }

    if(temp=="Customer")
    {
        CustomerMenus* cm=new CustomerMenus();
        this->hide();
         cm->show();



    }

}
