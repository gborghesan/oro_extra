local state, trans, conn = rfsm.state, rfsm.trans, rfsm.conn
fsm_loader=require('fsm_loader')
local load_rfsm=fsm_loader.load_rfsm
local fsm_dir = "fsm_test_files/"
return state{
	--call with some parameters
	state1 = load_rfsm(fsm_dir .. "state_fnc.lua",
		{['param11'] = 1,
		 ['param12'] = 2}),
	--call with some other parameters
	state2 = load_rfsm(fsm_dir .. "state_fnc.lua",
		{['param21'] = 3,
		 ['param22'] = 4}),
	--call with no parameters	 
	state3 = load_rfsm(fsm_dir .. "state_fnc.lua"),

	state4 = load_rfsm(fsm_dir .. "state.lua"),  
	  
	 trans {src="initial", tgt="state1"},
	 trans {src="state1", tgt="state2"},
	 trans {src="state2", tgt="state3"},
	 trans {src="state3", tgt="state4"},
}
