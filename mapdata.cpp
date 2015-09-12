#include "mapdata.h"
#include "ui_mapdata.h"

MapData::MapData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapData)
{
    ui->setupUi(this);
    this->setupModel();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->lineEdit,0);
    mapper->addMapping(ui->plainTextEdit,1);

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
    model = new QStandardItemModel(5, 2, this);

    QStringList namaNama;
    namaNama << "Joko" << "Slamet" << "Budi" << "Anto" << "Raharjo";

    QStringList alamat;
    alamat << "Kandeman, Batang"
           << "Semarang Jawa Tengah"
           << "Jakarta Indonesia"
           << "Tokyo Japan"
           << "Hongkong";

    for (int row =0; row < 5; ++row) {
        QStandardItem * item = new QStandardItem(namaNama[row]);
        model->setItem(row,0,item);
        item = new QStandardItem(alamat[row]);
        model->setItem(row,1,item);
    }
}

void MapData::tombolApdet(int row)
{
    ui->tmbPrev->setEnabled(row > 0);
    ui->tmbNext->setEnabled(row < model->rowCount() - 1);
}
