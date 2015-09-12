#include "mapdata.h"
#include "ui_mapdata.h"

MapData::MapData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapData)
{
    ui->setupUi(this);
    this->setupModel();

    QSqlTableModel *relModel = model->relationModel(typeIndex);
    ui->comboBox->setModel(relModel);
    ui->comboBox->setModelColumn(relModel->fieldIndex("description"));

//    mapper = new QDataWidgetMapper(this);
//    mapper->setModel(model);
//    mapper->addMapping(ui->lineEdit,0);
//    mapper->addMapping(ui->plainTextEdit,1);
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->lineEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->plainTextEdit, model->fieldIndex("address"));
    mapper->addMapping(ui->comboBox, typeIndex);

    connect(ui->tmbPrev,SIGNAL(clicked()),mapper,SLOT(toPrevious()));
    connect(ui->tmbNext,SIGNAL(clicked()),mapper,SLOT(toNext()));
    connect(mapper,SIGNAL(currentIndexChanged(int)),this,SLOT(tombolApdet(int)));
    mapper->toFirst();
}

MapData::~MapData()
{
    delete ui;
}

void MapData::setupModel()
{
//    model = new QStandardItemModel(5, 2, this);

//    QStringList namaNama;
//    namaNama << "Joko" << "Slamet" << "Budi" << "Anto" << "Raharjo";

//    QStringList alamat;
//    alamat << "Kandeman, Batang"
//           << "Semarang Jawa Tengah"
//           << "Jakarta Indonesia"
//           << "Tokyo Japan"
//           << "Hongkong";

//    for (int row =0; row < 5; ++row) {
//        QStandardItem * item = new QStandardItem(namaNama[row]);
//        model->setItem(row,0,item);
//        item = new QStandardItem(alamat[row]);
//        model->setItem(row,1,item);
//    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(0, tr("Cannot open database"),
            tr("Unable to establish a database connection.\n"
               "This example needs SQLite support. Please read "
               "the Qt SQL driver documentation for information how "
               "to build it."), QMessageBox::Cancel);
        return;
    }

    QSqlQuery query;
    query.exec("create table person (id int primary key, "
               "name varchar(20), address varchar(200), typeid int)");
    query.exec("insert into person values(1, 'Alice', "
               "'<qt>123 Main Street<br/>Market Town</qt>', 101)");
    query.exec("insert into person values(2, 'Bob', "
               "'<qt>PO Box 32<br/>Mail Handling Service"
               "<br/>Service City</qt>', 102)");
    query.exec("insert into person values(3, 'Carol', "
               "'<qt>The Lighthouse<br/>Remote Island</qt>', 103)");
    query.exec("insert into person values(4, 'Donald', "
               "'<qt>47338 Park Avenue<br/>Big City</qt>', 101)");
    query.exec("insert into person values(5, 'Emma', "
               "'<qt>Research Station<br/>Base Camp<br/>"
               "Big Mountain</qt>', 103)");

    query.exec("create table addresstype (id int, description varchar(20))");
    query.exec("insert into addresstype values(101, 'Home')");
    query.exec("insert into addresstype values(102, 'Work')");
    query.exec("insert into addresstype values(103, 'Other')");

    model = new QSqlRelationalTableModel(this);
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    typeIndex = model->fieldIndex("typeid");

    model->setRelation(typeIndex,
           QSqlRelation("addresstype", "id", "description"));
    model->select();
}

void MapData::tombolApdet(int row)
{
    ui->tmbPrev->setEnabled(row > 0);
    ui->tmbNext->setEnabled(row < model->rowCount() - 1);
}
