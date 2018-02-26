#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTime"
#include "udp.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_genButton_clicked()
{
    ui->listWidget->clear();
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    int n = qrand() % 31 + 20;

    for(int i = 0; i < n; i++) {
        ui->listWidget->addItem(QString::number(qrand()));
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Xml"),"/",tr("Xml files (*.xml)"));
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("list");
    for (int i=0; i<ui->listWidget->count(); i++)
    {
        xml.writeStartElement("row");
        xml.writeCharacters(ui->listWidget->item(i)->text());
        xml.writeEndElement();
    }
    xml.writeEndElement();
    xml.writeEndDocument();
    file.close();
}

void MainWindow::on_loadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Xml"),"/",tr("Xml files (*.xml)"));
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    ui->listWidget->clear();
    QXmlStreamReader xml;
    xml.setDevice(&file);
    xml.readNext();
    while(!xml.atEnd())
    {
        if(xml.isStartElement() && xml.name() == "row") {
            ui->listWidget->addItem(xml.readElementText());
        }
        xml.readNext();
    }
    file.close();
}

void MainWindow::on_sendButton_clicked()
{
    QByteArray Data;

    for (int i=0; i<ui->listWidget->count(); i++)
    {
            Data.append(ui->listWidget->item(i)->text());

    }

    UDP client;
    client.SayHello();
}
