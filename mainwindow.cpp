/**
 * @file MainWindow.cpp
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief Implementation file for the MainWindow class.
 *
 * This source file contains the implementation of the MainWindow class,
 * which sets up the main window of the application. It includes the setup of
 * MQTT client connections and subscriptions. The file demonstrates the integration
 * of the InputMqttClient and OutputMqttClient classes into a Qt-based user interface.
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "inputmqttclient.h"
#include "outputmqttclient.h"

///
/// @brief Constructs a MainWindow object.
/// @param parent The parent widget, default is nullptr.
///
/// This constructor initializes the main window, setting up the user interface
/// and connecting the MQTT clients to their respective brokers and topics.
///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input_1->connectToBroker("broker.hivemq.com", 1883);
    ui->input_1->setTopic("A/topic1");

    // Connecting the QPushButton's clicked signal to InputMqttClient's publishMessage slot
    connect(ui->send_input_1, &QPushButton::clicked, ui->input_1, &InputMqttClient::publishMessage);

    ui->input_2->connectToBroker("broker.hivemq.com", 1883);
    ui->input_2->setTopic("A/topic2");

    connect(ui->send_input_2, &QPushButton::clicked, ui->input_2, &InputMqttClient::publishMessage);

    ui->output_1->connectToBroker("broker.hivemq.com", 1883);
    ui->output_1->subscribeToTopic("A/topic1", 1);

    ui->output_2->connectToBroker("broker.hivemq.com", 1883);
    ui->output_2->subscribeToTopic("A/+", 1); // using wildcards to subscribe to multiple topics with a single subscription
}

///
/// @brief Destructor for MainWindow.
///
/// Cleans up the UI components when the MainWindow object is destroyed.
///
MainWindow::~MainWindow()
{
    delete ui;
}
