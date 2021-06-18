local tc=rtt.getTC();
local prop={}
for i =1,4 do
	prop[i]=rtt.Property("double","d" .. tostring(i),
    "a property")
	tc:addProperty(prop[i])
end

outport_commands = rtt.OutputPort("std_msgs.String", "commands_out")    -- global variable!
tc:addPort(outport_commands)

sendCommand=function (str)
    s=rtt.Variable("std_msgs.String")
    s.data="c_" ..str
    outport_commands:write(s)
end

dummyfunc =function()
    infomsg("dummyfunc called")
end


--[[ it is also possible to get operation form other components
local component1 = tc:getPeer("component1")
operation1 = component1:getOperation("operation1")
--]]
