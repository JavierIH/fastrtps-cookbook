#include <fastrtps/Domain.h>

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>

#include "messagePubSubTypes.h"

using namespace eprosima;
using namespace eprosima::fastrtps;


class SubListener : public SubscriberListener{
public:
	SubListener() : n_matched(0),n_msg(0){};
	~SubListener(){};
	void onSubscriptionMatched(Subscriber* sub,MatchingInfo& info){};
	void onNewDataMessage(Subscriber* sub);
	SampleInfo_t m_info;
	int n_matched;
	int n_msg;
};


int main(int argc, char** argv){
	// Create RTPSParticipant
	ParticipantAttributes participant_params;
	participant_params.rtps.setName("helloworld_subscriber_participant");
	Participant *participant = Domain::createParticipant(participant_params);
	if(participant == nullptr)
			return false;

	// Register the type
	MessagePubSubType message_type;
	Domain::registerType(participant,(TopicDataType*) &message_type);

	// Create Subscriber
	SubscriberAttributes subscriber_params;
	subscriber_params.topic.topicDataType = message_type.getName();
	subscriber_params.topic.topicName = "helloworld_topic";
	SubListener subscriber_listener;
	Subscriber *subscriber = Domain::createSubscriber(participant,subscriber_params,(SubscriberListener*)&subscriber_listener);
	if(subscriber == nullptr)
		return false;

	std::cin.ignore();
	return 0;
}

void SubListener::onNewDataMessage(Subscriber* sub){
	// Take data
	Message message;
	if(sub->takeNextData(&message, &m_info)){
		if(m_info.sampleKind == ALIVE){
			cout << "Message received: " << message.text();
			cout << " " << message.index() << endl;
			fflush(stdout);
		}
	}
}
