#include <mosquitto.h>
#include <iostream>

using namespace std;


// Example calss of MQTT - Untested
// Is not in the A*.hpp

class MQTTClient {
public:
    // Constructor
    MQTTClient() {
        // Initialize Mosquitto library
        mosquitto_lib_init();
        // Create a new Mosquitto instance
        mosq_ = mosquitto_new(NULL, true, this);

        // Check if instance creation was successful
        if (!mosq_) {
            cerr << "Failed to create mosquitto instance." << endl;
            exit(-1);
        }

        // Set callbacks for connection and message reception
        mosquitto_connect_callback_set(mosq_, &MQTTClient::onConnectStatic);
        mosquitto_message_callback_set(mosq_, &MQTTClient::onMessageStatic);
    }

    // Destructor
    ~MQTTClient() {
        // Disconnect and stop the Mosquitto loop
        mosquitto_disconnect(mosq_);
        mosquitto_loop_stop(mosq_, true);
        // Destroy the Mosquitto instance
        mosquitto_destroy(mosq_);
        // Cleanup Mosquitto library
        mosquitto_lib_cleanup();
    }

    // Connect to the MQTT broker
    void connect(const string& host, int port, int keepalive) {
        int ret = mosquitto_connect(mosq_, host.c_str(), port, keepalive);

        // Check for connection errors
        if (ret) {
            cerr << "Can't connect to MQTT broker" << endl;
            exit(-1);
        }

        // Start the Mosquitto loop in a separate thread
        mosquitto_loop_start(mosq_);
    }

    // Subscribe to an MQTT topic
    void subscribe(const string& topic) {
        mosquitto_subscribe(mosq_, NULL, topic.c_str(), 0);
    }

    // Run the main loop until user presses Enter
    void runLoop() {
        cout << "Press Enter to quit..." << endl;
        cin.get();
    }

private:
    // Static callback for connection events
    static void onConnectStatic(struct mosquitto *mosq, void *obj, int rc) {
        static_cast<MQTTClient*>(obj)->onConnect(mosq, rc);
    }

    // Static callback for message reception events
    static void onMessageStatic(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
        static_cast<MQTTClient*>(obj)->onMessage(mosq, msg);
    }

    // Callback for handling connection events
    void onConnect(struct mosquitto *mosq, int rc) {
        // Check for connection errors
        if (rc) {
            cerr << "Error with result code: " << rc << endl;
            exit(-1);
        }

        // Subscribe to predefined topics upon successful connection
        subscribe("0/test1");
        // Add more topics as needed
    }

    // Callback for handling received messages
    void onMessage(struct mosquitto *mosq, const struct mosquitto_message *msg) {
        // Print received message and topic
        cout << "Received message '" << (char *)msg->payload << "' on topic '" << msg->topic << "'" << endl;
    }

    // Mosquitto instance
    struct mosquitto *mosq_;
};

// Main function
int main() {
    // Create an instance of the MQTTClient class
    MQTTClient mqttClient;
    // Connect to the MQTT broker
    mqttClient.connect("test.mosquitto.org", 1883, 60);

    // You can subscribe to more topics or perform other operations here
    // mqttClient.subscribe("additional/topic");

    // Run the main loop until the user presses Enter
    mqttClient.runLoop();

    return 0;
}
