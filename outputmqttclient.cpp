/**
 * @file OutputMqttClient.cpp
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief Source file implementing the OutputMqttClient class functionallity
 */

#include "outputmqttclient.h"

///
/// \brief Constructs an OutputMqttClient object.
/// \param parent The parent widget, default is nullptr.
///
OutputMqttClient::OutputMqttClient(QWidget *parent)
    : QPlainTextEdit(parent), m_client(new QMqttClient(this)) {
    m_sum = 0;
    connect(m_client, &QMqttClient::messageReceived, this, &OutputMqttClient::onMessageReceived);
    connect(m_client, &QMqttClient::connected, this, &OutputMqttClient::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, [this](){ appendPlainText("Disconnected from broker."); });
}

///
/// \brief Connects to the MQTT broker.
/// \param hostname The hostname or IP of the MQTT broker.
/// \param port The network port of the MQTT broker, default MQTT port is 1883.
///
void OutputMqttClient::connectToBroker(const QString &hostname, quint16 port) {
    m_client->setHostname(hostname);
    m_client->setPort(port);
    m_client->connectToHost();
}

///
/// \brief Subscribes to a given MQTT topic.
/// \param topic The MQTT topic to subscribe to.
/// \param qos The Quality of Service level for the subscription.
///
void OutputMqttClient::subscribeToTopic(const QString &topic, quint8 qos) {
    m_topic = topic;
    m_qos = qos;
}

///
/// \brief Slot that gets executed when the client is connected to the broker.
/// Subscribes to the specified MQTT topic if not empty.
///
void OutputMqttClient::onConnected() {
    appendPlainText("Connected to broker.");

    if (!m_topic.isEmpty()) {
        auto subscription = m_client->subscribe(m_topic, m_qos);
        if (!subscription) {
            appendPlainText("Unable to create subscription object.");
            return;
        }

        connect(subscription, &QMqttSubscription::stateChanged, this, [this, subscription](QMqttSubscription::SubscriptionState state) {
            if (state == QMqttSubscription::Subscribed)
                appendPlainText("Successfully subscribed to topic.");
            else if (state == QMqttSubscription::Error)
                appendPlainText("Subscription error.");
        });
    }
}

///
/// \brief This slot gets executed when a message is received.
/// \param message The received message.
/// \param topic The topic from which the message was received.
///
void OutputMqttClient::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic) {

    // Converting the message to an integer
    bool ok;
    int value = message.toInt(&ok);

    if (ok) {
        m_sum += value; // Adding the new value to the total sum
        this->appendPlainText(QString("Received: %1, Total Sum: %2").arg(value).arg(m_sum));
    } else {
        this->appendPlainText("Error!");
    }
}
