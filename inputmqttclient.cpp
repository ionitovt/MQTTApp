#include "inputmqttclient.h"
#include <QIntValidator>


InputMqttClient::InputMqttClient(QWidget *parent)
    : QLineEdit(parent), m_client(new QMqttClient(this)) {
    this->setValidator(new QIntValidator(this));
    // Connect the signal that the QLineEdit emits when its text is edited
    connect(this, &QLineEdit::textEdited, this, &InputMqttClient::publishMessage);
}

void InputMqttClient::connectToBroker(const QString &hostname, quint16 port) {
    m_client->setHostname(hostname);
    m_client->setPort(port);
    m_client->connectToHost();
}

void InputMqttClient::setTopic(const QString &topic) {
    m_topic = topic;
}

void InputMqttClient::publishMessage() {
    if (m_client->state() == QMqttClient::Connected && !m_topic.isEmpty()) {
        m_client->publish(m_topic, this->text().toUtf8());
    }
}
