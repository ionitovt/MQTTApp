#ifndef OUTPUTMQTTCLIENT_H
#define OUTPUTMQTTCLIENT_H

#include <QPlainTextEdit>
#include <QMqttClient>

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
