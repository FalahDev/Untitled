#ifndef MAPDATA_H
#define MAPDATA_H

#include <QDialog>
//#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDataWidgetMapper>

namespace Ui {
class MapData;
}

class MapData : public QDialog
{
    Q_OBJECT

public:
    explicit MapData(QWidget *parent = 0);
    ~MapData();

private slots:
    void tombolApdet(int row);

private:
    Ui::MapData *ui;
    void setupModel();

    //QStandardItemModel *model;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper  *mapper;
    int typeIndex;
};

#endif // MAPDATA_H
