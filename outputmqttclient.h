/**
 * @file OutputMqttClient.h
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief File containing the OutputMqttClient class definition.
 *
 * This file contains the definition of the OutputMqttClient class, which extends
 * QPlainTextEdit to include MQTT subscription and message display capabilities. The class
 * allows the application to subscribe to MQTT topics and display received messages.
 * It serves as part of a larger project aimed at demonstrating MQTT integration.
 */

#ifndef OUTPUTMQTTCLIENT_H
#define OUTPUTMQTTCLIENT_H

#include <QPlainTextEdit>
#include <QMqttClient>

///
/// \class OutputMqttClient
/// \brief The OutputMqttClient class extends QPlainTextEdit to provide MQTT subscription and message display capabilities.
///
/// This class integrates MQTT subscription functionality with a QPlainTextEdit widget,
/// allowing the application to display messages received from MQTT topics.
///
class OutputMqttClient : public QPlainTextEdit
{

public:
    OutputMqttClient(QWidget *parent = nullptr);
    void connectToBroker(const QString &hostname, quint16 port);
    void subscribeToTopic(const QString &topic, quint8 qos);

private slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void onConnected();

private:
    QMqttClient *m_client;
    int m_sum;
    QString m_topic;
    quint8 m_qos;
};

#endif // OUTPUTMQTTCLIENT_H
