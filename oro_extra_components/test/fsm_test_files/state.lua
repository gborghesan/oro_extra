local state, trans, conn = rfsm.state, rfsm.trans, rfsm.conn

--local variables
local iteration = 1

return state{
	entry =	function(fsm) 
		infomsg('State without parameters, still access to functions.')
		dummyfunc()
	end
}

