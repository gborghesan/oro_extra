#include "oro_extra/rtt_period_counter.h"
#include <numeric>
namespace RTT {
PeriodCounter::PeriodCounter(TaskContext* tc,
							 std::string name_of_service,
							 int averaged_sample):
	tc_pointer_(tc),
	name_of_service_(name_of_service),
	averaged_sample_(averaged_sample){
	init();

}

PeriodCounter::PeriodCounter(RTT::TaskContext*  tc,
							 int averaged_sample):
	tc_pointer_(tc),
	name_of_service_(""),
	averaged_sample_(averaged_sample){
	init();
}

void PeriodCounter::SetBufferSize(unsigned int averaged_sample){
	averaged_sample_=averaged_sample;
	sample_buffer_.clear();
	sample_buffer_.reserve(averaged_sample);
	sample_index_=0;
	first_iteration_=true;
	downsample_=5;
}

void PeriodCounter::init(){
	if (std::string("")==name_of_service_){
		service_used_=false;
		tc_pointer_->addPort("time_average_outport",time_average_outport_);
		tc_pointer_->addAttribute("averaged_sample",averaged_sample_);
		tc_pointer_->addProperty("downsample",downsample_);
		tc_pointer_->addOperation("SetBufferSize",&PeriodCounter::SetBufferSize,this);
		//tc_pointer_->addOperation("Configure", &PeriodCounter::Configure,this);
		tc_pointer_->addOperation("Update", &PeriodCounter::Update,this);

	}else{
		service_used_=true;
		tc_pointer_->provides(name_of_service_)->addPort("time_average_outport",time_average_outport_);
		tc_pointer_->provides(name_of_service_)->addAttribute("averaged_sample",averaged_sample_);
		tc_pointer_->provides(name_of_service_)->addProperty("downsample",downsample_);
		tc_pointer_->provides(name_of_service_)->addOperation("SetBufferSize",
															  &PeriodCounter::SetBufferSize,this);
		//tc_pointer_->provides(name_of_service_)->addOperation("Configure",
		//													  &PeriodCounter::Configure,this);
		tc_pointer_->provides(name_of_service_)->addOperation("Update",
															  &PeriodCounter::Update,this);

	}

	SetBufferSize(averaged_sample_);

}

double  PeriodCounter::Update(){
	if (first_iteration_){//first iteration
		time_begin_loop_=os::TimeService::Instance()->getTicks();
		first_iteration_=false;
		return -1;
	}
	//measure time from last call
	double time_passed=os::TimeService::Instance()->secondsSince(time_begin_loop_);
	time_begin_loop_=os::TimeService::Instance()->getTicks();

		if (sample_buffer_.size()<averaged_sample_){//filling up the buffer
		sample_buffer_.push_back(time_passed);
	} else {
		sample_buffer_[sample_index_]=time_passed;
		sample_index_++;
		if (sample_index_==averaged_sample_)
			sample_index_=0;
	}


	std_msgs::Float64 time_passed_average;
	time_passed_average.data = std::accumulate(sample_buffer_.begin(), sample_buffer_.end(), 0.0);
	time_passed_average.data = time_passed_average.data /double(sample_buffer_.size());
	downsample_counter_++;
	//std::cout<<"downsample_counter_ "<<downsample_counter_<<std::endl;

	if (downsample_counter_>=downsample_){

		time_average_outport_.write(time_passed_average);
		downsample_counter_=0;
	}
	return time_passed_average.data;
}



}//end of namespace
/*
RTT::TaskContext* tc_pointer_;
std::string name_;

unsigned int averaged_sample_;
unsigned int downsample_;
std::vector<double> sample_buffer_;




public:
PeriodCounter(std::string name_of_service_="");
PeriodCounter(int);
PeriodCounter(std::string name_of_service_, int average_sample=10);
void setBufferSize(unsigned int);
*/
