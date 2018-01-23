#include <rtt/os/main.h>
#include "../src-cmp/event_echo-component.hpp"

#include <gtest/gtest.h>
using namespace RTT;
using namespace std;

TEST(event_echo, from_ros)
{
  //test for an event-triggered function
  //a string is write as ros message and rewritten as a std::string

  oro_extra::event_echo_component echo("echo");

  RTT::base::PortInterface*  events_inport= echo.getPort("events_inport");
  RTT::base::PortInterface*  events_outport= echo.getPort("events_outport");

  EXPECT_TRUE(echo.setActivity( new Activity(1, 0.0 )));
  EXPECT_TRUE(echo.configure());
  EXPECT_TRUE(echo.start());
  RTT::OutputPort<std_msgs::String> events_inport_out;
  RTT::InputPort<std::string> events_outport_in;
  EXPECT_TRUE(events_inport_out.connectTo(events_inport,RTT::ConnPolicy::data()));
  EXPECT_TRUE(events_outport->connectTo(&events_outport_in,RTT::ConnPolicy::data()));
  std_msgs::String s;
  s.data="example_string_in";

  events_inport_out.write(s);
  echo.engine()->loop();
  std::string sout;
  events_outport_in.read(sout);
  EXPECT_EQ(sout,s.data);
}

TEST(event_echo, to_ros)
{
  //test similar to before, other way around

  oro_extra::event_echo_component echo("echo");

  RTT::base::PortInterface*  events_to_ros_inport = echo.getPort("events_to_ros_inport");
  RTT::base::PortInterface*  events_to_ros_outport= echo.getPort("events_to_ros_outport");

  EXPECT_TRUE(echo.setActivity( new Activity(1, 0.0 )));
  EXPECT_TRUE(echo.configure());
  EXPECT_TRUE(echo.start());
  RTT::InputPort<std_msgs::String>events_outport_in ;
  RTT::OutputPort<std::string> events_inport_out;
  EXPECT_TRUE(events_inport_out.connectTo(events_to_ros_inport,RTT::ConnPolicy::data()));
  EXPECT_TRUE(events_to_ros_outport->connectTo(&events_outport_in,RTT::ConnPolicy::data()));
  std::string sin("example_string_in");
  std_msgs::String sout;

  events_inport_out.write(sin);
  echo.engine()->loop();

  events_outport_in.read(sout);
  EXPECT_EQ(sout.data,sin);
}

int ORO_main(int argc, char** argv)
{

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
