#ifndef INPUTMQTTCLIENT_H
#define INPUTMQTTCLIENT_H

#include <QLineEdit>
#include <QMqttClient>

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
