#include <fastrtps/Domain.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/publisher/PublisherListener.h>
#include <fastrtps/utils/eClock.h>

#include "messagePubSubTypes.h"

using namespace eprosima;
using namespace eprosima::fastrtps;


int main(int argc, char** argv){
	// Create RTPSParticipant
	ParticipantAttributes participant_params;
	participant_params.rtps.setName("helloworld_publisher_participant");
	Participant *participant = Domain::createParticipant(participant_params);
	if(participant == nullptr)
		return false;

	// Register the type
	MessagePubSubType message_type;
	Domain::registerType(participant,(TopicDataType*) &message_type);

	// Create Publisher
	PublisherAttributes publisher_params;
	publisher_params.topic.topicDataType = message_type.getName();
	publisher_params.topic.topicName = "helloworld_topic";
	Publisher *publisher = Domain::createPublisher(participant,publisher_params);
	if(publisher == nullptr)
		return false;

	// Publication code
	Message message;
	message.text("Hello World!");
	message.index(0);
	int index = 0;
	while(1){
		index++;
		message.index(index);
		publisher->write(&message);
		cout << "Message sent with index " << message.index() << endl;
		eClock::my_sleep(1000);
	}

	return 0;
}
