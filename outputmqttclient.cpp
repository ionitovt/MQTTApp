#include "outputmqttclient.h"

OutputMqttClient::OutputMqttClient(QWidget *parent)
    : QPlainTextEdit(parent), m_client(new QMqttClient(this)) {
    m_sum = 0;
    connect(m_client, &QMqttClient::messageReceived, this, &OutputMqttClient::onMessageReceived);
    connect(m_client, &QMqttClient::connected, this, &OutputMqttClient::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, [this](){ appendPlainText("Disconnected from broker."); });
}

void OutputMqttClient::connectToBroker(const QString &hostname, quint16 port) {
    m_client->setHostname(hostname);
    m_client->setPort(port);
    m_client->connectToHost();
}

void OutputMqttClient::subscribeToTopic(const QString &topic, quint8 qos) {
    m_topic = topic;
    m_qos = qos;
}

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
