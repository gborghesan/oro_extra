#ifndef EVENT_ECHO_COMPONENT_HPP
#define EVENT_ECHO_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <std_msgs/String.h>
namespace  oro_extra{
class event_echo_component : public RTT::TaskContext{
public:
	event_echo_component(std::string const& name);



private:
	RTT::InputPort  <std::string>				events_to_ros_inport_;
	RTT::InputPort	<std_msgs::String>	events_inport_;
	RTT::OutputPort <std::string>				events_outport_;
	RTT::OutputPort <std_msgs::String>	events_to_ros_outport_;


	void event_callback(RTT::base::PortInterface* portInterface);
	void event_to_ros_callback(RTT::base::PortInterface* portInterface);
	std_msgs::String event;
};
}
#endif
