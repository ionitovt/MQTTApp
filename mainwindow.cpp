#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "inputmqttclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input_1->connectToBroker("broker.hivemq.com", 1883);
    ui->input_1->setTopic("topic1");

    // Connecting the QPushButton's clicked signal to InputMqttClient's publishMessage slot
    connect(ui->send_input_1, &QPushButton::clicked, ui->input_1, &InputMqttClient::publishMessage);

    ui->input_2->connectToBroker("broker.hivemq.com", 1883);
    ui->input_2->setTopic("topic2");

    connect(ui->send_input_2, &QPushButton::clicked, ui->input_2, &InputMqttClient::publishMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
