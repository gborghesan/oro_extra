require "rttlib"
rttlib.color=true
require "complete"
require "readline"


--require "rttros"
msgs=require("messages")
errmsg ,warnmsg, infomsg =msgs.err,msgs.warn ,msgs.info
rtt.setLogLevel("Warning")
--execute a command that returns true or false, if it return false it gives an error
check_com=msgs.check_com;

gs=rtt.provides()
tc=rtt.getTC()
if tc:getName() == "lua" then
  depl=tc:getPeer("Deployer")
elseif tc:getName() == "Deployer" then
  depl=tc
end
depl:import("rtt_ros")
ros = gs:provides("ros")
ros:import("rtt_rospack")
ros:import("rtt_std_msgs")

base_dir = ros:find("oro_extra")

depl:loadComponent("fsm_comp", "OCL::LuaComponent")
fsm_comp = depl:getPeer("fsm_comp")
fsm_comp:exec_file(base_dir..
    "/scripts/rtt_components/fsm_component.lua")
fsm_comp:getProperty("state_machine")
	:set(base_dir.."/test/fsm_test_files/fsm.lua")
fsm_comp:getProperty("additional_code")
	:set(base_dir.."/test/fsm_test_files/fsm_extra_commands.lua")
fsm_comp:getProperty("viz_on"):set(false)
fsm_comp:setPeriod(1)	
fsm_comp:configure()
fsm_comp:start()
