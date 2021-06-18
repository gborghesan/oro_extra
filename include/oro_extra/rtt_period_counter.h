#ifndef RTT_PERIOD_COUNTER_H
#define RTT_PERIOD_COUNTER_H

#include <rtt/os/TimeService.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/Port.hpp>

#include <std_msgs/Float64.h>



namespace RTT {
class  PeriodCounter{
private:
	RTT::os::TimeService::ticks               time_begin_loop_;
	RTT::os::TimeService::Seconds             time_passed_loop_;
	RTT::OutputPort<std_msgs::Float64>		  time_average_outport_;
	RTT::OutputPort <std_msgs::Float64>		  time_std_outport_;

	RTT::TaskContext* tc_pointer_;
	std::string name_of_service_;

	unsigned int averaged_sample_;
	unsigned int sample_index_;
	unsigned int downsample_;
	unsigned int downsample_counter_;
	std::vector<double> sample_buffer_;
	bool service_used_;
	bool first_iteration_;

	void init();

public:
	PeriodCounter(RTT::TaskContext*  tc,int);
	PeriodCounter(RTT::TaskContext*  tc,std::string name_of_service_="", int average_sample=10);

	void SetBufferSize(unsigned int);
	double Update();




	typedef boost::shared_ptr<PeriodCounter> Ptr;


};


}//end namespace



#endif
