#ifndef PUBSUB_H
#define PUBSUB_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Subscriber
{
public:
	virtual void receiveMessage(string channel, string message, void* data) = 0; 
};

class PubSub
{
private:
	static map<string, vector<Subscriber*>> subscribers;

public:
	static void subscribe(string channel, Subscriber* subscriber); // subscribe to a channel
	static void unsubscribe(string channel, Subscriber* subscriber); // unsubscribe from a channel
	static void publish(string channel, string message, void* data); // publish a message to a channel
};

#endif
