/**
 * @file InputMqttClient.cpp
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief Source file implementing the InputMqttClient class functionallity
 */

#include "inputmqttclient.h"
#include <QIntValidator>

///
/// \brief Constructs an InputMqttClient object.
/// \param parent The parent widget, default is nullptr.
///
InputMqttClient::InputMqttClient(QWidget *parent)
    : QLineEdit(parent), m_client(new QMqttClient(this)) {
    // We restrict the User input to only number characters
    this->setValidator(new QIntValidator(this));
}

///
/// \brief Connects to the MQTT broker.
/// \param hostname The hostname or IP of the MQTT broker.
/// \param port The network port of the MQTT broker, default MQTT port is 1883.
///
void InputMqttClient::connectToBroker(const QString &hostname, quint16 port) {
    m_client->setHostname(hostname);
    m_client->setPort(port);
    m_client->connectToHost();
}

///
/// \brief Sets the MQTT topic for publishing messages.
/// \param topic The MQTT topic to publish to.
///
void InputMqttClient::setTopic(const QString &topic) {
    m_topic = topic;
}

///
/// \brief Publishes the current text to the MQTT topic.
///
void InputMqttClient::publishMessage() {
    if (m_client->state() == QMqttClient::Connected && !m_topic.isEmpty()) {
        m_client->publish(m_topic, this->text().toUtf8());
    }
}
