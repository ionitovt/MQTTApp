/**
 * @file InputMqttClient.h
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief File containing the InputMqttClient class definition.
 *
 * This file contains the definition of the InputMqttClient class, which extends
 * the functionality of QLineEdit to include MQTT publishing capabilities. The class
 * allows for text input from the user and publishing this input to a specified MQTT topic.
 * It serves as part of a larger project aimed at demonstrating MQTT integration.
 */

#ifndef INPUTMQTTCLIENT_H
#define INPUTMQTTCLIENT_H

#include <QLineEdit>
#include <QMqttClient>

///
/// \class InputMqttClient
/// \brief The InputMqttClient class extends QLineEdit to provide MQTT publishing capabilities.
///
/// This class is designed to integrate MQTT publishing with a QLineEdit widget,
/// allowing the user to input text and publish it to an MQTT topic.
///
class InputMqttClient : public QLineEdit {
    Q_OBJECT

public:
    InputMqttClient(QWidget *parent = nullptr);
    void connectToBroker(const QString &hostname, quint16 port);
    void setTopic(const QString &topic);
    void publishMessage();

private:
    QMqttClient *m_client;
    QString m_topic;
};

#endif // INPUTMQTTCLIENT_H
