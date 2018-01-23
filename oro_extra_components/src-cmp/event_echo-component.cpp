#include "event_echo-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>


using namespace  oro_extra;

event_echo_component::event_echo_component(std::string const& name) : TaskContext(name){
	addEventPort("events_inport",
							 events_inport_,
							 boost::bind(&event_echo_component::event_callback,this,_1));
	addEventPort("events_to_ros_inport",
							 events_to_ros_inport_,
							 boost::bind(&event_echo_component::event_to_ros_callback,this,_1));
	addPort("events_outport",events_outport_);
	addPort("events_to_ros_outport",events_to_ros_outport_);

	event.data.reserve(20);
}

void event_echo_component::event_callback(RTT::base::PortInterface* portInterface){
	event.data.clear();

	events_inport_.read(event);
	events_outport_.write(event.data);

}
void event_echo_component::event_to_ros_callback(RTT::base::PortInterface* portInterface){
	event.data.clear();

	events_to_ros_inport_.read(event.data);
	events_to_ros_outport_.write(event);
}



ORO_CREATE_COMPONENT(oro_extra::event_echo_component)
